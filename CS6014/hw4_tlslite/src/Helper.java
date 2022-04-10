import javax.crypto.Mac;
import javax.crypto.interfaces.DHPrivateKey;
import javax.crypto.spec.SecretKeySpec;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
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
    private static final String CaCertificatePath = "./resources/certs/CAcertificate.pem";

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

    public static BigInteger getDHPublicKey(BigInteger dhPrivateKey) {
        return GENERATOR.modPow(dhPrivateKey, PRIME);
    }

    public static byte[] getSignedKey(DHPrivateKey rsaPrivateKey, BigInteger dhPublicKey) throws NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initSign(rsaPrivateKey);
        signature.update(dhPublicKey.toByteArray());
        return signature.sign();
    }

    public static byte[] hdkfExpand(byte[] input, String tag) throws NoSuchAlgorithmException, InvalidKeyException {
        byte[] tagArr = new byte[tag.getBytes().length + 1];
        byte[] temp = tag.getBytes();
        System.arraycopy(temp, 0, tagArr, 0, tagArr.length - 1);
        tagArr[tagArr.length - 1] = 1;

        final Mac HMAC = Mac.getInstance("HmacSHA256");
        SecretKeySpec secretKeySpec = new SecretKeySpec(input, "HmacSHA256");
        HMAC.init(secretKeySpec);

        byte[] okm = HMAC.doFinal(tagArr);
        byte[] out = new byte[16];
        System.arraycopy(okm, 0, out, 0, out.length);

        return out;
    }

    public static boolean verifyCertificate(Certificate certificate) throws FileNotFoundException, CertificateException {
        Certificate CaCertificate = getCertificate(CaCertificatePath);
        try {
            certificate.verify(CaCertificate.getPublicKey());
            return true;
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (NoSuchProviderException e) {
            e.printStackTrace();
        } catch (SignatureException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static boolean verifyClient(Certificate clientCert, BigInteger clientDHPublicKey,
                                       byte[] clientSignedDHPublicKey) throws FileNotFoundException,
            CertificateException, NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        if(!verifyCertificate(clientCert)) { // Verify client certificate with CA certificate.
            System.out.println("Failed to verify certificate.");
            return false;
        }

        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initVerify(clientCert);
        signature.update(clientDHPublicKey.toByteArray());

        return signature.verify(clientSignedDHPublicKey);
    }

    public static BigInteger getDHSharedSecret(BigInteger DHKey, BigInteger privateKey) {
        return DHKey.modPow(privateKey, PRIME);
    }

    public static byte[] prepareMessage(byte[] message, SecretKeySpec MAC) throws NoSuchAlgorithmException,
            InvalidKeyException {
        Mac HMAC = Mac.getInstance("HmacSHA256");
        HMAC.init(MAC);
        return HMAC.doFinal(message);
    }

    public static byte[] concatenate(byte[] byteArray1, byte[] byteArray2) {
        int n = byteArray1.length + byteArray2.length;
        byte[] temp = new byte[n];
        for(int i = 0; i < n; i++) {
            if(i < byteArray1.length) {
                temp[i] = byteArray1[i];
            }
            else {
                temp[i] = byteArray2[i - byteArray1.length];
            }
        }
        return temp;
    }
}


