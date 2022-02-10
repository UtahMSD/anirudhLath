import java.io.*;
import java.util.Arrays;
import java.util.Objects;

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


    void writeBytes(ByteArrayOutputStream stream) throws IOException {
        if (DNSServer.debug > 0) {
            System.out.println("<--- DECODED QUESTION DATA --->");
            System.out.println("LABELS:         " + Arrays.deepToString(LABELS));
            System.out.println("QTYPE:          " + QTYPE);
            System.out.println("QCLASS:         " + QCLASS);

        }
        DataOutputStream out = new DataOutputStream(stream);
        for (int j = 0; j < LABELS.length; j++) {
            out.writeByte(LABELS[j].toCharArray().length);
            for (char c : LABELS[j].toCharArray()) {
                out.writeByte(c);
            }
        }
        out.writeByte(0);
        out.writeShort(QTYPE);
        out.writeShort(QCLASS);
    }


    @Override
    public String toString() {
        return "DNSQuestion{" +
                "LABELS=" + Arrays.toString(LABELS) +
                ", QTYPE=" + QTYPE +
                ", QCLASS=" + QCLASS +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DNSQuestion that = (DNSQuestion) o;
        return QTYPE == that.QTYPE && QCLASS == that.QCLASS && Arrays.equals(LABELS, that.LABELS);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(QTYPE, QCLASS);
        result = 31 * result + Arrays.hashCode(LABELS);
        return result;
    }

}
