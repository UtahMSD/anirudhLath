import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;

public class DNSRecord {
    String[] NAME;
    int TYPE;
    int CLASS;
    int TTL;
    int RDLENGTH;
    byte[] RDATA; // TODO: Byte[]

    public DNSRecord(DataInputStream stream, DNSMessage message) throws IOException {

        // Data extracted based on rfc1035
        NAME = message.readDomainName(stream);
        TYPE = stream.readUnsignedShort();
        CLASS = stream.readUnsignedShort();
        TTL = stream.readInt();
        RDLENGTH = stream.readUnsignedShort();
        RDATA = stream.readNBytes(RDLENGTH);

        if (DNSServer.debug > 0) {
            System.out.println("<--- DECODED RECORD DATA --->");
            System.out.println("NAME:           " + Arrays.deepToString(NAME));
            System.out.println("TYPE:           " + TYPE);
            System.out.println("CLASS:          " + CLASS);
            System.out.println("TTL:            " + TTL);
            System.out.println("RDLENGTH:       " + RDLENGTH);
            System.out.println("RDATA:          " + Arrays.deepToString(new byte[][]{RDATA}) + "\n");
        }

    }

    public static DNSRecord decodeRecord(ByteArrayInputStream inputStream, DNSMessage message) throws IOException {
        return new DNSRecord(new DataInputStream(inputStream), message);
    }

    // TODO: writeBytes(ByteArrayOutputStream, HashMap<String, Integer>)

    // TODO: String toString()

    // TODO: boolean timestampValid() -- return whether the creation date + the time to live is after the current
    //  time. The Date and Calendar classes will be useful for this.

}

