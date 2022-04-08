import javax.crypto.Mac;
import javax.crypto.interfaces.DHPrivateKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.SignatureException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;

public class Server {
    // Static Member Variables
    private static int PORT = 8080;
    private static final String certificatePath = "./resources/certs/CASignedServerCertificate.pem";
    private static final String privateKeyPath = "./resources/keys/serverPrivateKey.der";
    private static final String outputFilePath = "./resources/outputs/server.txt";

    // Member Variables
    private byte[] nonce;
    private Socket socket;
    private ServerSocket serverSocket;
    private Certificate signedServerCertificate;
    private DHPrivateKey rsaPrivateKey;
    private BigInteger dhPublicKey;
    private byte[] signedKey;

    // Keys
    private SecretKeySpec serverEncrypt;
    private SecretKeySpec clientEncrypt;
    private SecretKeySpec serverMAC;
    private SecretKeySpec clientMAC;
    private IvParameterSpec serverIV;
    private IvParameterSpec clientIV;

    public Server() throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException {
        this.signedServerCertificate = Helper.getCertificate(certificatePath);
        this.rsaPrivateKey = Helper.getRSAPrivateKey(privateKeyPath);
        this.dhPublicKey = Helper.getDHPublicKey(this.rsaPrivateKey);
        this.signedKey = Helper.getSignedKey(rsaPrivateKey, dhPublicKey);

        this.serverSocket = new ServerSocket(PORT);
        this.socket = serverSocket.accept();
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



}
