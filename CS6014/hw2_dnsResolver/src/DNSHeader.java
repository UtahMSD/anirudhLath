import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;

public class DNSHeader {
    int ID;
    int FLAGS;
    int QR;
    int OPCODE;
    int AA;
    int TC;
    int RD;
    int RA;
    int Z;
    int RCODE;
    int QDCOUNT;
    int ANCOUNT;
    int NSCOUNT;
    int ARCOUNT;

    public DNSHeader(DataInputStream stream) throws IOException {
        // Data extracted based on rfc1035
        ID = stream.readUnsignedShort();

        FLAGS = stream.readUnsignedShort();
        QR      = FLAGS & 0b1000000000000000;
        OPCODE  = FLAGS & 0b0111100000000000;
        AA      = FLAGS & 0b0000010000000000;
        TC      = FLAGS & 0b0000001000000000;
        RD      = FLAGS & 0b0000000100000000;
        RA      = FLAGS & 0b0000000010000000;
        Z       = FLAGS & 0b0000000001110000;
        RCODE   = FLAGS & 0b0000000000001111;

        QDCOUNT = stream.readUnsignedShort();
        ANCOUNT = stream.readUnsignedShort();
        NSCOUNT = stream.readUnsignedShort();
        ARCOUNT = stream.readUnsignedShort();

        if (DNSServer.debug > 0) {
            System.out.println("<--- DECODED HEADER DATA --->");
            System.out.println("ID:         " + ID);
            System.out.println("QR:         " + QR);
            System.out.println("OPCODE:     " + OPCODE);
            System.out.println("AA:         " + AA);
            System.out.println("TC:         " + TC);
            System.out.println("RD:         " + RD);
            System.out.println("RA:         " + RA);
            System.out.println("Z:          " + Z);
            System.out.println("RCODE:      " + RCODE);
            System.out.println("QDCOUNT:    " + QDCOUNT);
            System.out.println("ANCOUNT:    " + ANCOUNT);
            System.out.println("NSCOUNT:    " + NSCOUNT);
            System.out.println("ARCOUNT:    " + ARCOUNT + "\n");
        }
    }
    public static DNSHeader decodeHeader(ByteArrayInputStream inputStream) throws IOException {
        return new DNSHeader(new DataInputStream(inputStream));
    }
}
