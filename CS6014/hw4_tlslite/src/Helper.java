import javax.crypto.interfaces.DHPrivateKey;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;

public class Helper {
    // https://www.ietf.org/rfc/rfc3526.txt, page 5
    private static final BigInteger GENERATOR = new BigInteger("2");
    private static final BigInteger PRIME = new BigInteger("FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1\n" +
            "      29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD\n" +
            "      EF9519B3 CD3A431B 302B0A6D F25F1437 4FE1356D 6D51C245\n" +
            "      E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED\n" +
            "      EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 49286651 ECE45B3D\n" +
            "      C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F\n" +
            "      83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D\n" +
            "      670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B\n" +
            "      E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9\n" +
            "      DE2BCBF6 95581718 3995497C EA956AE5 15D22618 98FA0510\n" +
            "      15728E5A 8AAAC42D AD33170D 04507A33 A85521AB DF1CBA64\n" +
            "      ECFB8504 58DBEF0A 8AEA7157 5D060C7D B3970F85 A6E1E4C7\n" +
            "      ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226 1AD2EE6B\n" +
            "      F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C\n" +
            "      BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31\n" +
            "      43DB5BFC E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7\n" +
            "      88719A10 BDBA5B26 99C32718 6AF4E23C 1A946834 B6150BDA\n" +
            "      2583E9CA 2AD44CE8 DBBBC2DB 04DE8EF9 2E8EFC14 1FBECAA6\n" +
            "      287C5947 4E6BC05D 99B2964F A090C3A2 233BA186 515BE7ED\n" +
            "      1F612970 CEE2D7AF B81BDD76 2170481C D0069127 D5B05AA9\n" +
            "      93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34063199\n" +
            "      FFFFFFFF FFFFFFFF", 16);

    public static Certificate getCertificate(String filename) throws CertificateException, FileNotFoundException {
        CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
        InputStream file = new FileInputStream(filename);
        return certificateFactory.generateCertificate(file);
    }

    public static DHPrivateKey getRSAPrivateKey(String filename) throws IOException, NoSuchAlgorithmException,
            InvalidKeySpecException {
        InputStream file = new FileInputStream(filename);
        PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(file.readAllBytes());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        return (DHPrivateKey) keyFactory.generatePrivate(keySpec);
    }

    public static BigInteger getDHPublicKey(DHPrivateKey rsaPrivateKey) {
        return GENERATOR.modPow(rsaPrivateKey.getX(), PRIME);
    }

    public static byte[] getSignedKey(DHPrivateKey rsaPrivateKey, BigInteger dhPublicKey) throws NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initSign(rsaPrivateKey);
        signature.update(dhPublicKey.toByteArray());
        return signature.sign();
    }

    public static byte[] hdkfExpand(byte[] prk, String server_encrypt) {
    }
}
