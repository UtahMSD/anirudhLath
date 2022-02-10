import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class DNSMessage {
    static byte[] receiveData;
    static byte[] backupData;
    DNSHeader header;
    DNSQuestion[] questions;
    DNSRecord[] answers;
    DNSRecord[] authorityRecords;
    DNSRecord[] additionalRecords;

    // TODO: How to check if the header is compressed?

    public DNSMessage(ByteArrayInputStream stream) throws IOException {
        if (DNSServer.debug > 0) {
            System.out.println("REQUEST STARTED -------------------------------------------------------------------->");
        }

        // Header Section
        header = DNSHeader.decodeHeader(stream);

        // Question Section
        questions = new DNSQuestion[header.QDCOUNT];
        for (int i = 0; i < header.QDCOUNT; i++) {
            questions[i] = DNSQuestion.decodeQuestion(stream, this);
        }

        // Answer Section
        answers = new DNSRecord[header.ANCOUNT];
        for (int i = 0; i < header.ANCOUNT; i++) {
            try {
                answers[i] = DNSRecord.decodeRecord(stream, this);
            } catch (EOFException e) {
                stream = new ByteArrayInputStream(backupData);
                additionalRecords[i] = DNSRecord.decodeRecord(stream, this);
            }
        }

        // Authority Section
        authorityRecords = new DNSRecord[header.NSCOUNT];
        for (int i = 0; i < header.NSCOUNT; i++) {
            try {
                authorityRecords[i] = DNSRecord.decodeRecord(stream, this);
            } catch (EOFException e) {
                stream = new ByteArrayInputStream(backupData);
                additionalRecords[i] = DNSRecord.decodeRecord(stream, this);
            }
        }

        // Additional Section
        additionalRecords = new DNSRecord[header.ARCOUNT];
        for (int i = 0; i < header.ARCOUNT; i++) {
            try {
                additionalRecords[i] = DNSRecord.decodeRecord(stream, this);
            } catch (EOFException e) {
                stream = new ByteArrayInputStream(backupData);
                additionalRecords[i] = DNSRecord.decodeRecord(stream, this);
            }
        }

        if (DNSServer.debug > 0) {
            System.out.println("<--- MESSAGE STATISTICS --->");
            System.out.println("HEADER:         " + header.toString());
            System.out.println("QUESTIONS:      " + Arrays.stream(questions).toList().toString());
            System.out.println("ANSWERS:        " + Arrays.stream(answers).toList().toString());
            System.out.println("AUTHORITY:      " + Arrays.stream(authorityRecords).toList().toString());
            System.out.println("ADDITIONAL:     " + Arrays.stream(additionalRecords).toList().toString());
        }

        if (DNSServer.debug > 0) {
            System.out.println("REQUEST ENDED " +
                    "---------------------------------------------------------------------->" + "\n");
        }
    }

    public DNSMessage(DNSMessage request, DNSRecord[] answers) {
        if (DNSServer.debug > 0) {
            System.out.println("RESPONSE STARTED " +
                    "-------------------------------------------------------------------->");
        }
        // Header
        this.header = DNSHeader.buildResponseHeader(request, this);

    }

    public static DNSMessage decodeMessage(byte[] receiveData) throws IOException {
        DNSMessage.receiveData = receiveData;
        return new DNSMessage(new ByteArrayInputStream(receiveData));
    }

    String[] readDomainName(DataInputStream stream) throws IOException {
        ArrayList<String> labels = new ArrayList<>();
        int firstOctet = stream.readByte();
        if (firstOctet != 0) {
            int charCount = firstOctet;
            StringBuilder label = new StringBuilder();
            for (int i = 0; i <= charCount; i++) {
                if (i != charCount) {
                    char c = (char) stream.readUnsignedByte();
                    label.append(c);
                } else {
                    labels.add(label.toString());
                    label = new StringBuilder();
                    charCount = stream.readUnsignedByte();
                    i = -1; // Offset -1 was necessary I am not exactly sure why

                    if (charCount == 0) {
                        break;
                    }
                }
            }
        }
        return labels.toArray(new String[0]);
    }

    String[] readDomainName(int firstByte) throws IOException {
        return readDomainName(new DataInputStream(new ByteArrayInputStream(receiveData, firstByte,
                receiveData.length)));
    }

    // TODO: static DNSMessage buildResponse(DNSMessage request, DNSRecord[] answers) --build a response based on the request and the answers you intend to send back.
    static DNSMessage buildResponse(DNSMessage request, DNSRecord[] answers) throws IOException {
        return new DNSMessage(request, answers);
    }

    // TODO: byte[] toBytes() -- get the bytes to put in a packet and send back
    byte[] toBytes() throws IOException {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        header.writeBytes(out);
        out.close();
        if (DNSServer.debug > 0) {
            System.out.println("RESPONSE ENDED " +
                    "---------------------------------------------------------------------->" + "\n");
        }
        return out.toByteArray();
    }


    // TODO: static void writeDomainName(ByteArrayOutputStream, HashMap<String,Integer> domainLocations, String[] domainPieces) -- If this is the first time we've seen this domain name in the packet, write it using the DNS encoding (each segment of the domain prefixed with its length, 0 at the end), and add it to the hash map. Otherwise, write a back pointer to where the domain has been seen previously.

    // TODO: String octetsToString(String[] octets) -- join the pieces of a domain name with dots ([ "utah", "edu"] -> "utah.edu" )
    String octetsToString(String[] octets) {
        StringBuilder builder = new StringBuilder();
        for(int i = 0; i < octets.length; i++) {
            builder.append(octets[i]);
            builder.append('.');
        }
        return builder.toString();
    }

    // TODO: String toString()

}
