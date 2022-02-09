import java.io.*;
import java.net.*;

public class DNSServer {
    DatagramPacket receivePacket;
    DatagramPacket googlePacket;
    DatagramPacket sendPacket;

    static DatagramSocket server_socket = null;

    InetAddress clientAddress;
    int clientPort;

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
        byte[] googleData = new byte[1024];
        byte[] sendData = new byte[1024];

        while(true) { // Start listening for requests
            DNSServer server = new DNSServer();

            // Receive
            server.receivePacket = new DatagramPacket(receiveData, receiveData.length);
            server_socket.receive(server.receivePacket);

            // Collect client data
            server.clientAddress = server.receivePacket.getAddress();
            server.clientPort = server.receivePacket.getPort();

            // Parse Packet
            DNSMessage message = DNSMessage.decodeMessage(receiveData);

            // TODO: Check Cache
            if(DNSCache.isCached(message)) {
                message.answers = new DNSRecord[1];
                message.answers[0] = DNSCache.fetchRecord(message);
                // TODO: Respond and also don't forget the AA of type 41 for DiG
            } else {
                InetAddress googleDNS = InetAddress.getByName("8.8.8.8");
                DatagramSocket googleSocket = new DatagramSocket();

                // Forward request to Google
                if(debug > 0) {
                    System.out.println("Sending packet to Google!");
                }
                server.sendPacket = new DatagramPacket(receiveData, receiveData.length, googleDNS,
                        53);
                googleSocket.send(server.sendPacket);
                if(debug > 0) {
                    System.out.println("Done, sent the packet to Google!\n");
                }

                // Prepare to receive answer from Google
                if(debug > 0) {
                    System.out.println("Preparing to receive answer from Google!");
                }
                server.googlePacket = new DatagramPacket(googleData, googleData.length);
                googleSocket.receive(server.googlePacket);
                if(debug > 0) {
                    System.out.println("Received answer from Google!");
                }

                DNSMessage googleMessage = DNSMessage.decodeMessage(googleData);

                // Put data in cache
                DNSCache.insertRecord(message, googleMessage);

                // Respond back
                server.sendPacket = new DatagramPacket(googleData, googleData.length, server.clientAddress,
                        server.clientPort);
                server_socket.send(server.sendPacket);

            }
                // TODO: If not in Cache, forward request to Google DNS Server
                    // TODO: Store Google response in personal Cache, only one answer
                // TODO: Else respond with the answer in Cache
                    // TODO: If there is an additional answer through DiG, send that record back in the response packet
            // TODO: If the host is nonexistent, the program should be able to respond correctly, which is?

        }
    }
}
