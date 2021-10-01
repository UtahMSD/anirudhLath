import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.Buffer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.*;

public class MyHttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server_socket = new ServerSocket(2121);
        while (true) {
            Socket s = server_socket.accept();
            InputStream input = s.getInputStream();
            InputStreamReader inputReader = new InputStreamReader(input);
            Scanner scanner = new Scanner(inputReader);

            String method = scanner.next();
            String file = scanner.next();
            String protocol = scanner.next();

            System.out.println("REQUEST");
            System.out.println(method + " " + file + " " + protocol);

            Map<String, String> detail = new HashMap<>();

            for (int i = 0; i < 5; i++) { // Only read the first five lines because the last one cause the program to stop working.
//                String line = scanner.nextLine();
//                System.out.println(line);
                String header = scanner.next();
                String desc = scanner.nextLine();
                detail.put(header, desc);
                System.out.println(header + " " + desc);
            }
            System.out.println("Loop exit");

            OutputStream output = s.getOutputStream();
            PrintWriter responder = new PrintWriter(output);

            file = file.substring(1);

            File response = new File(file);



            if (file.equals("")) {
                response = new File("index.html");
            } else {

                System.out.println(file);
                response = new File(file);
            }

            String responseStatusCode;
            if (!response.exists()) {
                responseStatusCode = "404 Bad Request";
            } else {
                responseStatusCode = "200 OK";
            }

            responder.write(protocol + " " + responseStatusCode + "\r\n" );

            for (Map.Entry<String , String> entry : detail.entrySet()) {
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
}
