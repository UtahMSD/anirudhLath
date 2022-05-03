import javax.crypto.Cipher;
import javax.crypto.Mac;
import javax.crypto.interfaces.DHPrivateKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

public class Client {
    // Static Member Variables
    private static int PORT = 8080;
    private static final String certificatePath = "./src/resources/certs/CASignedClientCertificate.pem";
    private static final String privateKeyPath = "./src/resources/keys/clientPrivateKey.der";
    private static final String encryptedFilePath = "./src/resources/outputs/encryptedFile.txt";
    private static final String decryptedFilePath = "./src/resources/outputs/decryptedFile.txt";

    // Member Variables
    private byte[] nonce;
    private Socket socket;
    private Certificate signedClientCertificate;
    private PrivateKey rsaPrivateKey;
    private BigInteger dhPublicKey;
    private BigInteger dhPrivateKey;
    private byte[] signedDHPublicKey;

    // Keys
    private SecretKeySpec serverEncrypt;
    private SecretKeySpec clientEncrypt;
    private SecretKeySpec serverMAC;
    private SecretKeySpec clientMAC;
    private IvParameterSpec serverIV;
    private IvParameterSpec clientIV;

    public Client() throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException {
        this.nonce = Helper.getNonceObject();
        this.signedClientCertificate = Helper.getCertificate(certificatePath);
        this.rsaPrivateKey = Helper.getRSAPrivateKey(privateKeyPath);
        this.dhPrivateKey = new BigInteger(Integer.toString(new SecureRandom().nextInt()));
        this.dhPublicKey = Helper.getDHPublicKey(this.dhPrivateKey);
        this.signedDHPublicKey = Helper.getSignedKey(this.rsaPrivateKey, this.dhPublicKey);
        this.socket = new Socket("127.0.0.1", PORT);
    }

    public void makeSecretKeys(byte[] nonce, byte[] sharedSecretKey) throws NoSuchAlgorithmException,
            InvalidKeyException {
        final Mac HMAC = Mac.getInstance("HmacSHA256");
        SecretKeySpec secretKeySpec = new SecretKeySpec(this.nonce, "HmacSHA256");
        HMAC.init(secretKeySpec);
        byte[] prk = HMAC.doFinal(sharedSecretKey);
        serverEncrypt = new SecretKeySpec(Helper.hdkfExpand(prk, "server encrypt"), "AES");
        clientEncrypt = new SecretKeySpec(Helper.hdkfExpand(serverEncrypt.getEncoded(), "client encrypt"), "AES");
        serverMAC = new SecretKeySpec(Helper.hdkfExpand(clientEncrypt.getEncoded(), "server MAC"), "AES");
        clientMAC = new SecretKeySpec(Helper.hdkfExpand(serverMAC.getEncoded(), "client MAC"), "AES");
        serverIV = new IvParameterSpec(Helper.hdkfExpand(clientMAC.getEncoded(), "server IV"));
        clientIV = new IvParameterSpec(Helper.hdkfExpand(serverIV.getIV(), "client IV"));
    }

    public static void main(String[] args) {
        try {
            // Initialise client
            System.out.println("Initializing client...");
            Client client = new Client();
            System.out.println("Done.");

            // Setup I/O streams
            System.out.println("Setting up I/O streams and history...");
            ObjectInputStream inputStream = new ObjectInputStream(client.socket.getInputStream());
            ObjectOutputStream outputStream = new ObjectOutputStream(client.socket.getOutputStream());
            ByteArrayOutputStream history = new ByteArrayOutputStream();
            System.out.println("Done.");

            // Send Nonce
            outputStream.flush();
            outputStream.writeObject(client.nonce);
            history.write(client.nonce);

            // Receive server certificate, DH public key, signed DH public key
            Certificate serverCertificate;
            BigInteger serverDHPublicKey;
            byte[] serverSignedDHPublicKey;

            serverCertificate = (Certificate) inputStream.readObject();
            serverDHPublicKey = (BigInteger) inputStream.readObject();
            serverSignedDHPublicKey = (byte[]) inputStream.readObject();

            history.write(serverCertificate.getEncoded());
            history.write(serverDHPublicKey.toByteArray());
            history.write(serverSignedDHPublicKey);

            // Send client certificate, DH public key, signed DH public key
            outputStream.writeObject(client.signedClientCertificate);
            outputStream.writeObject(client.dhPublicKey);
            outputStream.writeObject(client.signedDHPublicKey);
            history.write(client.signedClientCertificate.getEncoded());
            history.write(client.dhPublicKey.toByteArray());
            history.write(client.signedDHPublicKey);

            // Verify Server
            if(!Helper.verifyHost(serverCertificate, serverDHPublicKey, serverSignedDHPublicKey)) {
                System.out.println("Server was not verified, program will stop. Re-run client to try again.");
                System.exit(1);
            } else {
                System.out.println("Host has been verified.");
            }

            // Calculate shared secret
            BigInteger secret = Helper.getDHSharedSecret(serverDHPublicKey, client.dhPrivateKey);
            System.out.println("Calculated the shared secret.");

            // Get MAC Keys
            client.makeSecretKeys(client.nonce, secret.toByteArray());
            System.out.println("Generated MACs.");

            // Receive server history and MAC and compare
            byte[] serverHistory = (byte[]) inputStream.readObject();
            byte[] clientHistory = Helper.prepareMessage(history.toByteArray(), client.serverMAC);

            if (!Arrays.equals(clientHistory, serverHistory)) {
                System.out.println("Invalid response from the server, the history doesn't match. Please try again.");
                System.exit(1);
            } else {
                System.out.println("History matched.");
            }

            // Send updated history to server
            history.write(serverHistory);
            byte[] message = Helper.prepareMessage(history.toByteArray(), client.clientMAC);
            outputStream.writeObject(message);


            System.out.println("Handshake complete.");

            // Receive and decrypt file
            System.out.println("Waiting for file...");
            byte[] encryptedData = (byte[]) inputStream.readObject();
            FileOutputStream fileOutputStream = new FileOutputStream(Client.encryptedFilePath);
            fileOutputStream.write(encryptedData);
            fileOutputStream.flush();
            fileOutputStream.close();
            System.out.println("Received file, decrypting...");


            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, client.serverEncrypt, client.serverIV);
            byte[] decryptedData = cipher.doFinal(encryptedData);

            fileOutputStream = new FileOutputStream(Client.decryptedFilePath);
            fileOutputStream.write(decryptedData);
            fileOutputStream.flush();
            fileOutputStream.close();
            System.out.println("Done.");

            // Send receipt (ACK)
            System.out.println("Acknowledging server that the file has been received.");
            String response = "File was received.";
            cipher.init(Cipher.ENCRYPT_MODE, client.clientEncrypt, client.clientIV);
            byte[] hashedResponseBytes = Helper.prepareMessage(response.getBytes(), client.clientEncrypt);
            byte[] concatBytes = Helper.concatenate(response.getBytes(), hashedResponseBytes);
            outputStream.writeObject(cipher.doFinal(concatBytes));
            outputStream.flush();
            outputStream.close();
            inputStream.close();
            System.out.println("Communication complete.");

        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

}
