import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;

public class DNSQuestion {
    String[] LABELS;
    int QTYPE;
    int QCLASS;

    public DNSQuestion(DataInputStream stream, DNSMessage message) throws IOException {

        // Data extracted based on rfc1035
        LABELS = message.readDomainName(stream);
        QTYPE = stream.readUnsignedShort();
        QCLASS = stream.readUnsignedShort();

        if (DNSServer.debug > 0) {
            System.out.println("<--- DECODED QUESTION DATA --->");
            System.out.println("LABELS:         " + Arrays.deepToString(LABELS));
            System.out.println("QTYPE:          " + QTYPE);
            System.out.println("QCLASS:         " + QCLASS);

        }
    }
    public static DNSQuestion decodeQuestion(ByteArrayInputStream inputStream, DNSMessage message) throws IOException {
        return new DNSQuestion(new DataInputStream(inputStream), message);
    }

    // TODO: void writeBytes(ByteArrayOutputStream, HashMap<String,Integer> domainNameLocations). Write the question bytes which will be sent to the client. The hash map is used for us to compress the message, see the DNSMessage class below.

    // TODO: toString()

    // TODO: equals()

    // TODO: hashCode()
}
