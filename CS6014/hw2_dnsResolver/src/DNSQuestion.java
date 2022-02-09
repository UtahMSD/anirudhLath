import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.ArrayList;

public class DNSQuestion {
    ArrayList<String> labels;
    int QTYPE;
    int QCLASS;

    public DNSQuestion(DataInputStream stream) throws IOException {
        labels = new ArrayList<>();

        // Data extracted based on rfc1035

        // Extract the labels
        int firstOctet = stream.readByte();
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
        }

        QTYPE = stream.readUnsignedShort();
        QCLASS = stream.readUnsignedShort();

        if (DNSServer.debug > 0) {
            System.out.println("<--- DECODED QUESTION DATA --->");
            System.out.println("LABELS:         " + labels.toString());
            System.out.println("QTYPE:          " + QTYPE);
            System.out.println("QCLASS:         " + QCLASS);

        }
    }
    public static DNSQuestion decodeQuestion(ByteArrayInputStream inputStream) throws IOException {
        return new DNSQuestion(new DataInputStream(inputStream));
    }
}
