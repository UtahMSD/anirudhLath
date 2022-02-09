import java.io.*;
import java.net.*;

public class DNSServer {
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

            // Parse Packet
            DNSMessage message = DNSMessage.decodeMessage(receiveData);
            // TODO: Check Cache
                // TODO: If not in Cache, forward request to Google DNS Server
                    // TODO: Store Google response in personal Cache, only one answer
                // TODO: Else respond with the answer in Cache
                    // TODO: If there is an additional answer through DiG, send that record back in the response packet
            // TODO: If the host is nonexistent, the program should be able to respond correctly, which is?

        }
    }
}
