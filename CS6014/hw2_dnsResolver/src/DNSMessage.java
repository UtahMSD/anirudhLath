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
        this.questions = request.questions;
        this.answers = answers;
        this.authorityRecords = request.authorityRecords;
        this.additionalRecords = request.additionalRecords;

        if (DNSServer.debug > 0) {
            System.out.println("<--- MESSAGE STATISTICS --->");
            System.out.println("HEADER:         " + header.toString());
            System.out.println("QUESTIONS:      " + Arrays.stream(questions).toList().toString());
            System.out.println("ANSWERS:        " + Arrays.stream(answers).toList().toString());
            System.out.println("AUTHORITY:      " + Arrays.stream(authorityRecords).toList().toString());
            System.out.println("ADDITIONAL:     " + Arrays.stream(additionalRecords).toList().toString() + "\n");
        }

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

    static DNSMessage buildResponse(DNSMessage request, DNSRecord[] answers) throws IOException {
        return new DNSMessage(request, answers);
    }

    byte[] toBytes() throws IOException {
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        header.writeBytes(out);

        for (int i = 0; i < questions.length; i++) {
            questions[i].writeBytes(out);
        }

        for (int i = 0; i < answers.length; i++) {
            answers[i].writeBytes(out);
        }

        for (int i = 0; i < authorityRecords.length; i++) {
            authorityRecords[i].writeBytes(out);
        }

        for (int i = 0; i < additionalRecords.length; i++) {
            additionalRecords[i].writeBytes(out);
        }
        out.close();

        if (DNSServer.debug > 0) {
            System.out.println("RESPONSE ENDED " +
                    "---------------------------------------------------------------------->" + "\n");
        }
        return out.toByteArray();
    }


    void writeDomainName(ByteArrayOutputStream stream) throws IOException {
        DataOutputStream out = new DataOutputStream(stream);
        for (int i = 0; i < questions.length; i++) {
            for (int j = 0; j < questions[i].LABELS.length; j++) {
                out.writeByte(questions[i].LABELS.length);
                for (char c : questions[i].LABELS[j].toCharArray()) {
                    out.writeInt(c);
                }
            }
        }
    }

    String octetsToString(String[] octets) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < octets.length; i++) {
            builder.append(octets[i]);
            builder.append('.');
        }
        return builder.toString();
    }

    @Override
    public String toString() {
        return "DNSMessage{" +
                "header=" + header +
                ", questions=" + Arrays.toString(questions) +
                ", answers=" + Arrays.toString(answers) +
                ", authorityRecords=" + Arrays.toString(authorityRecords) +
                ", additionalRecords=" + Arrays.toString(additionalRecords) +
                '}';
    }


}
