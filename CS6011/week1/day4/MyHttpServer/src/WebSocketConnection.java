import java.io.DataInputStream;
import java.net.Socket;

public class WebSocketConnection {
    Socket webSocket;
    DataInputStream inputStream;

    public WebSocketConnection(handleClient client) {
        webSocket = client.s;
        inputStream = new DataInputStream(client.input);


    }
}
