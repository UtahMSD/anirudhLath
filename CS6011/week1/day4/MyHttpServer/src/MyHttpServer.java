import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
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
     String file;
     String protocol;
     Map<String, String> detail;
     String header;
     String desc;

    // Output variables for handling the HTTPResponse
     OutputStream output;
     PrintWriter responder;

     File response;
     String responseStatusCode;

    /*// Request and Response Objects
     HTTPRequest request;
     HTTPResponse answer;*/

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
        file = scanner.next();
        protocol = scanner.next();
        file = file.substring(1); // Removes the '/' char for the filepath.

        // Prints out the HTTP Request in the console to make debugging easier.
        System.out.println(method + " " + file + " " + protocol);

        // Create a map of all the details
        detail = new HashMap<>();
        for (int i = 0; i < 7; i++) { // Only read the first seven lines based Safari's HTTP Header Request.
            header = scanner.next();
            desc = scanner.nextLine();
            detail.put(header, desc);
//            System.out.println(header + " " + desc);
        }
        System.out.println(protocol + "\n");
    }

    public void HTTPResponse() throws IOException {

        // Assign values to the necessary variables to handle the HTTP Response.
        output = s.getOutputStream();
        response = new File(file);
        responder = new PrintWriter(output);

        // Check if the filepath is specified and if not, respond with the default webpage, i.e. 'index.html', otherise continue.
        if (file.equals("")) {
            response = new File("index.html");
        }

        // Check if the filepath specified exists, and if not throw a FileNotFoundException and respond with status code '404 Bad Request', otherwise respond with status code '200 OK'.
        if (!response.exists()) {
            responseStatusCode = "404 Bad Request";
            throw new FileNotFoundException( "404: Bad Request!");
        } else {
            responseStatusCode = "200 OK";
        }

        // Start writing to the output stream
        responder.write(protocol + " " + responseStatusCode + "\r\n"); // Respond with the header.

        for (Map.Entry<String, String> entry : detail.entrySet()) { // Respond with the details captured in the HTTPRequest since I don't know what the appropriate response should be.
            responder.println(entry.getKey() + " " + entry.getValue());
        }

        responder.println("\r\n"); // Break the line to start returning the content section of the response.

        // Respond with the requested file, line by line.
        scanner = new Scanner(response);
        while (scanner.hasNextLine()) {
            responder.println(scanner.nextLine());
        }

        // Flush the responder and the output to finish writing to the output stream.
        responder.flush();
        output.flush();

        // Close the connection with the client that requested this connection.
        s.close();
    }


    public static void main(String[] args) throws IOException {
        final MyHttpServer server = new MyHttpServer(); // Initialise the server

        Runnable runnable = new Runnable() {
            public void run() {
                System.out.println("Server handled a request on thread " + Thread.currentThread().getId());
                while (true) {
                    try { // Try the logic but if it fails move on to catch and handle the exceptions.
                        server.s = server_socket.accept();
                        server.HTTPRequest();
                        Thread.sleep(100);
                        server.HTTPResponse();
                    } catch (FileNotFoundException fnf) { // Handle the server in case the request file by the user was not found.
                        System.out.println("404 File not Found! Bad Request!");

                        // Redirected user to the 404 webpage to let them know of the issue.
                        server.file = "404.html";
                        try {
                            server.HTTPResponse();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    } catch (IOException ioe) { // I am not sure what kind of errors would be classified as IOExceptions.
                        System.out.println("IOException!");
                    } catch (Exception e) { // Handle any other exceptions and avoid interrupting the webserver.
                        e.printStackTrace();
                        System.out.println("This is confusing!");
                    }
                }
            }
        };

        if(server_socket.accept() != null) {
            new Thread(runnable).start();
        }



    }
}
