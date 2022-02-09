import java.io.*;
import java.net.*;

public class DNSServer {
    ByteArrayInputStream inputStream;
    ByteArrayOutputStream outputStream;
    DatagramPacket receivePacket;
    DatagramPacket sendPacket;
    static DatagramSocket server_socket = null;

    static int debug = 1;

    public static void main(String[] args) throws IOException {

        final int PORT_NUMBER = 8053;




        // Open a socket on PORT_NUMBER
        try {
            server_socket = new DatagramSocket(PORT_NUMBER);
        } catch (SocketException e) {
            if(debug > 1) {
                e.printStackTrace();
            }
            System.out.println("Unable to create server socket. Program will now exit.");
            System.exit(1);
        }

        byte[] receiveData = new byte[1024];
        byte[] sendData = new byte[1024];

        while(true) { // Start listening for requests
            DNSServer server = new DNSServer();

            // Receive
            server.receivePacket = new DatagramPacket(receiveData, receiveData.length);
            server_socket.receive(server.receivePacket);
            server.inputStream = new ByteArrayInputStream(server.receivePacket.getData(), server.receivePacket.getOffset(), server.receivePacket.getLength());

            // Parse Packet
            DNSHeader header = DNSHeader.decodeHeader(server.inputStream);
            DNSQuestion question = DNSQuestion.decodeQuestion(server.inputStream);
            DNSRecord record = DNSRecord.decodeRecord(server.inputStream);

        }
    }
}
