import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.Arrays;

public class DNSMessage {
    DNSHeader header;
    DNSQuestion[] questions;
    DNSRecord[] answers;
    DNSRecord[] authorityRecords;
    DNSRecord[] additionalRecords;

    public DNSMessage(ByteArrayInputStream stream) throws IOException {
        if (DNSServer.debug > 0) {
            System.out.println("MESSAGE STARTED -------------------------------------------------------------------->");
        }

        // Header Section
        header = DNSHeader.decodeHeader(stream);

        // Question Section
        questions = new DNSQuestion[header.QDCOUNT];
        for(int i = 0; i < header.QDCOUNT; i++) {
            questions[i] = DNSQuestion.decodeQuestion(stream);
        }

        // Answer Section
        answers = new DNSRecord[header.ANCOUNT];
        for(int i = 0; i < header.ANCOUNT; i++) {
            answers[i] = DNSRecord.decodeRecord(stream);
        }

        // Authority Section
        authorityRecords = new DNSRecord[header.NSCOUNT];
        for(int i = 0; i < header.NSCOUNT; i++) {
            authorityRecords[i] = DNSRecord.decodeRecord(stream);
        }

        // Additional Section
        additionalRecords = new DNSRecord[header.ARCOUNT];
        for(int i = 0; i < header.ARCOUNT; i++) {
            additionalRecords[i] = DNSRecord.decodeRecord(stream);
        }

        if(DNSServer.debug > 0) {
            System.out.println("<--- MESSAGE STATISTICS --->");
            System.out.println("HEADER:         " + header.toString());
            System.out.println("QUESTIONS:      " + Arrays.stream(questions).toList().toString());
            System.out.println("ANSWERS:        " + Arrays.stream(answers).toList().toString());
            System.out.println("AUTHORITY:      " + Arrays.stream(authorityRecords).toList().toString());
            System.out.println("ADDITIONAL:     " + Arrays.stream(additionalRecords).toList().toString());
        }

        if (DNSServer.debug > 0) {
            System.out.println("MESSAGE ENDED ---------------------------------------------------------------------->" + "\n");
        }
    }

    public static DNSMessage decodeMessage(byte[] receiveData) throws IOException {
        return new DNSMessage(new ByteArrayInputStream(receiveData));
    }
}
