import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.security.Key;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.*;

public class MyHttpServer {

    // Basic server variables.
    static ServerSocket server_socket;
    Socket s;

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


    public MyHttpServer() throws IOException {
        server_socket = new ServerSocket(8080); // Initialise the server on port 8080.
    }

    public void HTTPRequest() throws IOException {

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

    public void HTTPResponse() throws IOException {

        // Assign values to the necessary variables to handle the HTTP Response.
        output = s.getOutputStream();
        response = new File(filePath);
        responder = new PrintWriter(output);
        responseDetails = new HashMap<>();
        contentType = Files.probeContentType(Path.of(filePath));
        System.out.println(contentType);
        responseDetails.put("ContentType:", contentType);

        // Check if the filepath is specified and if not, respond with the default webpage, i.e. 'index.html', otherise continue.
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
        for (Map.Entry<String, String> entry: responseDetails.entrySet()) {
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


    public static void main(String[] args) throws IOException {
        final MyHttpServer server = new MyHttpServer(); // Initialise the server

        Runnable runnable = new Runnable() {
            public void run() {
                System.out.println("Server handled a request on thread " + Thread.currentThread().getId());

            }
        };

        while (true) {
            try { // Try the logic but if it fails move on to catch and handle the exceptions.
                server.s = server_socket.accept();
                server.HTTPRequest();
                //Thread.sleep(100);
                server.HTTPResponse();
            } catch (FileNotFoundException fnf) { // Handle the server in case the request file by the user was not found.
                System.out.println("404 File not Found! Bad Request!");

                // Redirected user to the 404 webpage to let them know of the issue.
                server.filePath = "404.html";
                try {
                    server.HTTPResponse();
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
}
