import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.*;

public class MyHttpServer {

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080); // Initialize the server

        while (true) {
            Socket client = server.accept(); // Check if a connection is requested
            System.out.println("New client connected" + client.getInetAddress().getHostAddress()); // Console output client connection data.

            handleClient clientConnection = new handleClient(client); // Create a client socket connection object that will handle everything in the server such as parsing the request and send the response.

            Thread t = new Thread(clientConnection); // Create a new thread if a connection is requested.
            t.start(); // Then start the thread.

        }
    }

    public static class handleClient implements Runnable {

        // Basic server variables.
        //static ServerSocket server_socket;
        private final Socket s;

        // Input variables for handling the HTTPRequest
        InputStream input;
        InputStreamReader inputReader;

        // Member Variables
        Scanner scanner;
        String method;
        String filePath;
        String protocol;
        Map<String, String> requestDetails;
        Map<String, String> responseDetails;
        String header;
        String desc;

        // Output variables for handling the HTTPResponse
        OutputStream output;
        PrintWriter responder;
        String contentType;

        File response;
        String responseStatusCode;


        public handleClient(Socket socket) {
            this.s = socket; // Tell the object about the socket that was trying to connect in main()
            // This will construct a client connection which can be used later in the main() function
            // which will allow the use of private functions to handle the I/O...
        }

        private void HTTPRequest() throws IOException {

            // Assign values to the variables that are necessary to handle the HTTPRequest.
            input = s.getInputStream();
            inputReader = new InputStreamReader(input);
            scanner = new Scanner(inputReader);

            // Populate member variables.
            method = scanner.next();
            filePath = scanner.next();
            protocol = scanner.next();
            filePath = filePath.substring(1); // Removes the '/' char for the filepath.

            // Prints out the HTTP Request in the console to make debugging easier.
            System.out.println(method + " " + filePath + " " + protocol);

            // Create a map of all the details
            requestDetails = new HashMap<>();
            for (int i = 0; i < 7; i++) { // Only read the first seven lines based Safari's HTTP Header Request.
                header = scanner.next();
                desc = scanner.nextLine();
                requestDetails.put(header, desc);
                System.out.println(header + " " + desc);
            }
            System.out.println(protocol + "\n");
        }

        private void HTTPResponse() throws IOException {

            // Assign values to the necessary variables to handle the HTTP Response.
            output = s.getOutputStream();
            response = new File(filePath);
            responder = new PrintWriter(output);
            responseDetails = new HashMap<>();
            contentType = Files.probeContentType(Path.of(filePath));
            System.out.println(contentType);
            responseDetails.put("Content-Type:", contentType);

            // Check if the filepath is specified and if not, respond with the default webpage, i.e. 'index.html', otherwise continue.
            if (filePath.equals("")) {
                response = new File("index.html");
            }

            // Check if the filepath specified exists, and if not throw a FileNotFoundException and respond with status code '404 Bad Request', otherwise respond with status code '200 OK'.
            if (!response.exists()) {
                responseStatusCode = "404 Bad Request";
                throw new FileNotFoundException("404: Bad Request!");
            } else {
                responseStatusCode = "200 OK";
            }

            // Start writing to the output stream
            responder.write(protocol + " " + responseStatusCode + "\r\n"); // Respond with the header.
            for (Map.Entry<String, String> entry : responseDetails.entrySet()) {
                responder.println(entry.getKey() + " " + entry.getValue() + "\n");
            }
            responder.flush();

            // Respond with bytes to a bufferedOutputStream.
            BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(output);
            byte[] responseByteData = new byte[(int) response.length()];
            FileInputStream fileInputStream = new FileInputStream(response);
            fileInputStream.read(responseByteData);
            for (byte responseByteDatum : responseByteData) {
                bufferedOutputStream.write(responseByteDatum);
            }
            bufferedOutputStream.flush();

            responder.write("\r\n\r\n");
            responder.flush();

            // Close the connection with the client that requested this connection.
            s.close();
        }

        @Override
        public void run() {
            System.out.println("Request handled by thread #" + Thread.currentThread().getId());
            //System.out.println("Server handled a request on thread " + Thread.currentThread().getId());
            try { // Try the logic but if it fails move on to catch and handle the exceptions.
                this.HTTPRequest();
                this.HTTPResponse();
            } catch (FileNotFoundException fnf) { // Handle the server in case the request file by the user was not found.
                System.out.println("404 File not Found! Bad Request!");

                // Redirected user to the 404 webpage to let them know of the issue.
                this.filePath = "404.html";
                try {
                    this.HTTPResponse();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } catch (IOException ioe) { // I am not sure what kind of errors would be classified as IOExceptions.
                System.out.println("IOException!");
                ioe.printStackTrace();
            } catch (Exception e) { // Handle any other exceptions and avoid interrupting the webserver.
                e.printStackTrace();
                System.out.println("This is confusing!");
            }
        }
    }

    /*static String generateResponseKey(String REQUESTED_WEBSOCKET_KEY) throws NoSuchAlgorithmException {
        final String MAGIC_KEY = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        String requestKey = REQUESTED_WEBSOCKET_KEY + MAGIC_KEY;
        MessageDigest shaEncoder = MessageDigest.getInstance("SHA-1");

        byte[] encoded = shaEncoder.digest( requestKey.getBytes());
        final String RESPONSE_KEY = Base64.getEncoder().encodeToString(encoded);

        return RESPONSE_KEY;
    }

    public static void main(String[] args) throws NoSuchAlgorithmException {
        String data = s.useDelimiter("\\r\\n\\r\\n").next();
        Matcher get = Pattern.compile("^GET").matcher(data);
        String REQUESTED_WEBSOCKET_KEY = "";



        Map<String, String> requestedDetails = new HashMap<>();
        Map<String, String> responseDetails = new HashMap<>();

        if (requestedDetails.containsKey("Sec-WebSocket-Key")) {
            REQUESTED_WEBSOCKET_KEY =  requestedDetails.get("Sec-WebSocket-Key");
        }

        responseDetails.put("Sec-WebSocket-Accept", generateResponseKey(REQUESTED_WEBSOCKET_KEY));




    }*/

}
