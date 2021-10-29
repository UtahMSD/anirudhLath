import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class clientRoom {
    static ArrayList<String> rooms_;
    static ArrayList<WebSocketConnection> clients_ = new ArrayList<>();
    static Map<String, ArrayList<WebSocketConnection>> clientRoomCollection = new HashMap<>();

    public clientRoom(WebSocketConnection client, String room) {
        clients_.add(client);
        clientRoomCollection.put(room, clients_);
    }
}
