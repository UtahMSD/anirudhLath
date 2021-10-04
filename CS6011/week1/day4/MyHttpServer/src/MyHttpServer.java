import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.*;

public class MyHttpServer {
    static ServerSocket server_socket;
    static Socket s;

    static InputStream input;
    static InputStreamReader inputReader;

    static Scanner scanner;
    static String method;
    static String file;
    static String protocol;
    static Map<String, String> detail;
    static String header;
    static String desc;

    static OutputStream output;
    static PrintWriter responder;

    static File response;
    static String responseStatusCode;

    static HTTPRequest request;
    static HTTPResponse answer;

    public MyHttpServer() throws IOException {
        server_socket = new ServerSocket(8080);
        Socket s = server_socket.accept();
    }

    public static class HTTPRequest {
        public HTTPRequest() throws IOException {
            input = s.getInputStream();
            inputReader = new InputStreamReader(input);
            scanner = new Scanner(inputReader);
            method = scanner.next();
            file = scanner.next();
            protocol = scanner.next();
            file = file.substring(1);

            detail = new HashMap<>();
            for (int i = 0; i < 7; i++) { // Only read the first seven lines based Safari's HTTP Header Request.
                header = scanner.next();
                desc = scanner.nextLine();
                detail.put(header, desc);
                System.out.println(header + " " + desc);
            }

            System.out.println("REQUEST");
            System.out.println(method + " " + file + " " + protocol);
        }
    }

    public static class HTTPResponse {
        public HTTPResponse() throws IOException {
            File response = new File(file);
            if (file.equals("")) {
                response = new File("index.html");
            }
            System.out.println(file);

            response = new File(file);
            if (!response.exists()) {
                responseStatusCode = "404 Bad Request";
                response = new File("index.html");
                throw new FileNotFoundException("File not found. 404 Bad Request.");
            } else {
                responseStatusCode = "200 OK";
            }

            responder.write(protocol + " " + responseStatusCode + "\r\n");

            for (Map.Entry<String, String> entry : detail.entrySet()) {
                responder.println(entry.getKey() + " " + entry.getValue());
            }

            responder.println("\r\n");

            scanner = new Scanner(response);
            while (scanner.hasNextLine()) {
                responder.println(scanner.nextLine());
            }

            responder.flush();
            output.flush();
            s.close();
        }
    }

    public static void main(String[] args) throws IOException {
        MyHttpServer server = new MyHttpServer();
        while (true) {

            request = new HTTPRequest();
            answer = new HTTPResponse();
        }
    }
}
