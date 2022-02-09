import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.ArrayList;

public class DNSRecord {
    ArrayList<String> labels;
    public DNSRecord(DataInputStream stream) throws IOException {
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
    }

    public static DNSRecord decodeRecord(ByteArrayInputStream inputStream) throws IOException {
        return new DNSRecord(new DataInputStream(inputStream));
    }
}
