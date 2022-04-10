import javax.crypto.*;
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

public class Server {
    // Static Member Variables
    private static int PORT = 8080;
    private static final String certificatePath = "./resources/certs/CASignedServerCertificate.pem";
    private static final String privateKeyPath = "./resources/keys/serverPrivateKey.der";
    private static final String inputFilePath = "./resources/inputs/server.txt";
    private static final String clientReceiptPath = "./resources/outputs/clientReceiptDecrypted.txt";

    // Member Variables
    private byte[] nonce;
    private Socket socket;
    private ServerSocket serverSocket;
    private Certificate signedServerCertificate;
    private DHPrivateKey rsaPrivateKey;
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

    public Server() throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException {
        this.signedServerCertificate = Helper.getCertificate(certificatePath);
        this.dhPrivateKey = new BigInteger(Integer.toString(new SecureRandom().nextInt()));
        this.rsaPrivateKey = Helper.getRSAPrivateKey(privateKeyPath);
        this.dhPublicKey = Helper.getDHPublicKey(this.dhPrivateKey);
        this.signedDHPublicKey = Helper.getSignedKey(rsaPrivateKey, dhPublicKey);

        this.serverSocket = new ServerSocket(PORT);
//        this.socket = serverSocket.accept();
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

    public static void main(String[] args) throws CertificateException, IOException, NoSuchAlgorithmException,
            InvalidKeySpecException, SignatureException, InvalidKeyException, ClassNotFoundException, NoSuchPaddingException, InvalidAlgorithmParameterException, IllegalBlockSizeException, BadPaddingException {

        // Initialise the server
        Server server = new Server();
        System.out.println("Server has been initialised.");

        while(true) {
            // Wait for connection
            server.socket = server.serverSocket.accept();
            System.out.println("Connection with a client has been established.");

            // Initialise I/O streams
            ObjectInputStream inputStream = new ObjectInputStream(server.socket.getInputStream());
            ObjectOutputStream outputStream = new ObjectOutputStream(server.socket.getOutputStream());
            System.out.println("Initialising I/O streams.");

            // Initialise byte stream for history
            ByteArrayOutputStream history = new ByteArrayOutputStream();

            // Handle nonce
            System.out.println("Attempting to start handshake...");
            server.nonce = (byte[]) inputStream.readObject();
            history.write(server.nonce);

            // Send server certificate, DH public key, signed DH public key
            outputStream.flush();
            outputStream.writeObject(server.signedServerCertificate);
            outputStream.writeObject(server.dhPublicKey);
            outputStream.writeObject(server.signedDHPublicKey);
            history.write(server.signedServerCertificate.getEncoded());
            history.write(server.dhPublicKey.toByteArray());
            history.write(server.signedDHPublicKey);

            // Receive client certificate, DH public key, signed DH public key
            Certificate clientCertificate;
            BigInteger clientDHPublicKey;
            byte[] clientSignedDHPublicKey;

            clientCertificate = (Certificate) inputStream.readObject();
            clientDHPublicKey = (BigInteger) inputStream.readObject();
            clientSignedDHPublicKey = (byte[]) inputStream.readObject();

            history.write(clientCertificate.getEncoded());
            history.write(clientDHPublicKey.toByteArray());
            history.write(clientSignedDHPublicKey);

            // Verify client
            if (!Helper.verifyClient(clientCertificate, clientDHPublicKey, clientSignedDHPublicKey)) {
                System.out.println("Client was not verified, program will move on to the next request.");
                continue;
            }
            System.out.println("Client has been verified.");

            // Calculate shared secret
            BigInteger secret = Helper.getDHSharedSecret(clientDHPublicKey, server.dhPrivateKey);
            System.out.println("Calculated the shared secret.");

            // Generate MAC
            server.makeSecretKeys(server.nonce, secret.toByteArray());
            System.out.println("Generated MACs.");

            // Respond with history and server MAC
            byte[] message = Helper.prepareMessage(history.toByteArray(), server.serverMAC);
            outputStream.writeObject(message);
            history.write(message);

            // Record client history and compare
            byte[] clientHistory = (byte[]) inputStream.readObject();
            byte[] serverHistory = Helper.prepareMessage(history.toByteArray(), server.clientMAC);

            if (!Arrays.equals(clientHistory, serverHistory)) {
                System.out.println("Invalid response from the client, the history doesn't match. Please try again.");
                continue;
            }
            System.out.println("Handshake complete.");

            // Prepare file to send
            System.out.println("Preparing file to send.");
            byte[] inputFileBytes = new FileInputStream(Server.inputFilePath).readAllBytes();
            byte[] hashedFileBytes = Helper.prepareMessage(inputFileBytes, server.serverEncrypt);
            byte[] concatBytes = Helper.concatenate(inputFileBytes, hashedFileBytes);

            // Encrypt data
            System.out.println("Encrypting file data.");
            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, server.serverEncrypt, server.serverIV);
            byte[] encryptedBytes = cipher.doFinal(concatBytes);
            outputStream.writeObject(encryptedBytes);
            System.out.println("Sent data to client.");

            // Await and receive client receipt
            byte[] clientReceipt = (byte[]) inputStream.readObject();
            System.out.println("Received client receipt.");
            cipher.init(Cipher.DECRYPT_MODE, server.clientEncrypt, server.clientIV);
            System.out.println("Decryting data.");
            byte[] decryptedReceipt = cipher.doFinal(clientReceipt);
            byte[] decrypted = new byte[decryptedReceipt.length - 32];

            for (int i = 0; i < decryptedReceipt.length - 32; i++) {
                decrypted[i] = decryptedReceipt[i];
            }
            System.out.println("Writing decrypted data to output logs at ./resources/outputs/clientReceiptDecrypted.txt.");
            FileOutputStream fileOutputStream = new FileOutputStream(Server.clientReceiptPath);
            fileOutputStream.write(decrypted);
            fileOutputStream.flush();
            fileOutputStream.close();
        }



    }

}
