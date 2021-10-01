import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.*;

public class MyHttpServer {
    public static void main(String[] args) throws IOException {
        while (true) {
            ServerSocket server_socket = new ServerSocket(8080);
            Socket s = server_socket.accept();
            InputStream input = s.getInputStream();
            Scanner scanner = new Scanner(input);

            String method = scanner.next();
            String file = scanner.next();
            String protocol = scanner.next();

            System.out.println("REQUEST");
            System.out.println(method + " " + file + " " + protocol);

            Map<String, String> detail = new HashMap<>();

            while (scanner.hasNext()) {
                String header = scanner.next();
                String desc = scanner.nextLine();
                detail.put(header, desc);
                System.out.println(header + " " + desc);
            }

            OutputStream output = s.getOutputStream();
            PrintWriter responder = new PrintWriter(output);

            responder.write("HTTP/1.0 200 OK\r\n");
            responder.write("Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n");
            responder.write("Server: Apache/0.8.4\r\n");
            responder.write("Content-Type: text/html\r\n");
            responder.write("Content-Length: 59\r\n");
            responder.write("Expires: Sat, 01 Jan 2000 00:59:59 GMT\r\n");
            responder.write("Last-modified: Fri, 09 Aug 1996 14:21:40 GMT\r\n");
            responder.write("\r\n");
            responder.write("<TITLE>Exemple</TITLE>");
            responder.write("<P>Ceci est une page d'exemple.</P>");
//
//            file = file.substring(1);
//
//            File response = new File(file);
//
//
//
//            if (file.equals("")) {
//                response = new File("index.html");
//            } else {
//
//                System.out.println(file);
//                response = new File(file);
//            }
//
//            String responseStatusCode;
//            if (!response.exists()) {
//                responseStatusCode = "404 Bad Request";
//            } else {
//                responseStatusCode = "200 OK";
//            }
//
//            responder.write(protocol + " " + responseStatusCode + "\r\n" );
//
//            for (Map.Entry<String , String> entry : detail.entrySet()) {
//                responder.println(entry.getKey() + " " + entry.getValue() + "\r\n");
//            }
//
//            responder.println("\r\n");
//
//            scanner = new Scanner(response);
//            while (scanner.hasNext()) {
//                responder.println(scanner.next() + "\r\n");
//            }
            responder.flush();
            s.close();
            input.close();
            output.close();
            //server_socket.close();
        }
    }
}
