import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.ArrayList;

public class DNSRecord {
    ArrayList<String> labels;
    int NAME;
    int TYPE;
    int CLASS;
    int TTL;
    int RDLENGTH;
    int RDATA;
    public DNSRecord(DataInputStream stream) throws IOException {
        labels = new ArrayList<>();

        // Data extracted based on rfc1035

        // Extract the labels
        int firstOctet = stream.readUnsignedShort();
        if(firstOctet != 0) {
            int charCount = firstOctet;
            StringBuilder label = new StringBuilder();
            for(int i = 0; i <= charCount; i++) {
                if (i != charCount) {
                    char c = (char) stream.readUnsignedByte();
                    label.append(c);
                } else {
                    labels.add(label.toString());
                    label = new StringBuilder();
                    charCount = stream.readUnsignedByte();
                    i = -1; // Offset -1 was necessary I am not exactly sure why

                    if(charCount == 0) {
                        break;
                    }
                }
            }
        } else {
            NAME = firstOctet;
        }

        TYPE = stream.readUnsignedShort();
        CLASS = stream.readUnsignedShort();
        TTL = stream.readInt();
        RDLENGTH = stream.readUnsignedShort();
        RDATA = stream.readUnsignedShort();
        if (DNSServer.debug > 0) {
            System.out.println("<--- DECODED RECORD DATA --->");
            System.out.println("NAME:           " + NAME);
            System.out.println("TYPE:           " + TYPE);
            System.out.println("CLASS:          " + CLASS);
            System.out.println("TTL:            " + TTL);
            System.out.println("RDLENGTH:       " + RDLENGTH);
            System.out.println("RDATA:          " + RDATA + "\n");
        }

    }

    public static DNSRecord decodeRecord(ByteArrayInputStream inputStream) throws IOException {
        return new DNSRecord(new DataInputStream(inputStream));
    }
}

