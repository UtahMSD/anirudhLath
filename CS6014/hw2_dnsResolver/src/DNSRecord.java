import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.PushbackInputStream;
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
        byte[] buf = stream.readAllBytes();
        stream = new DataInputStream(new ByteArrayInputStream(buf));
        DataInputStream bufstream = new DataInputStream(new ByteArrayInputStream(buf));
        int temp = bufstream.readShort();
        if (DNSServer.debug == 2) {
            System.out.println(Integer.toBinaryString(temp));
            System.out.println(temp & 0b1100000000000000);
            System.out.println(temp & 0b0011111111111111);
        }
        int offset = 0;
        if((temp & 0b1100000000000000) == 49152) {
            offset = temp & 0b0011111111111111;
            if(DNSServer.debug > 0) {
                System.out.println("<--- COMPRESSION FOUND --->");
                System.out.println("OFFSET:         " + offset);
            }
            NAME = message.readDomainName(offset);
            stream.readUnsignedShort(); // I had to add padding for some reason
        } else {
            NAME = message.readDomainName(stream);
        }

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

        // Backup Bytes
        DNSMessage.backupData = stream.readAllBytes(); // Had to backup bytes because Java is the stupidest language.

    }

    public static DNSRecord decodeRecord(ByteArrayInputStream inputStream, DNSMessage message) throws IOException {
        return new DNSRecord(new DataInputStream(inputStream), message);
    }

    // TODO: writeBytes(ByteArrayOutputStream, HashMap<String, Integer>)

    @Override
    public String toString() {
        return "DNSRecord{" +
                "NAME=" + Arrays.toString(NAME) +
                ", TYPE=" + TYPE +
                ", CLASS=" + CLASS +
                ", TTL=" + TTL +
                ", RDLENGTH=" + RDLENGTH +
                ", RDATA=" + Arrays.toString(RDATA) +
                '}';
    }


    // TODO: boolean timestampValid() -- return whether the creation date + the time to live is after the current
    //  time. The Date and Calendar classes will be useful for this.

}

