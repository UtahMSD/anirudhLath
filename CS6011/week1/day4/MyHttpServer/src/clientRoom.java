import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class clientRoom {
    static ArrayList<String> rooms_;
    static ArrayList<WebSocketConnection> roomClients_ = new ArrayList<>();
    static ArrayList<WebSocketConnection> allClients_ = new ArrayList<>();
    static Map<String, ArrayList<WebSocketConnection>> clientRoomCollection = new HashMap<>();

    public clientRoom(WebSocketConnection client, String room) {
        allClients_.add(client);
        for (Map.Entry<String, ArrayList<WebSocketConnection>> entry : clientRoomCollection.entrySet()) {
            if (entry.getKey() == room) {
                for (WebSocketConnection checkClient : entry.getValue()) {
                    if (client != checkClient) {
                        entry.getValue().add(client);
                        System.out.println("fired");
                    }
                }
            }
        }
        clientRoomCollection.put(room, roomClients_);
        System.out.println(clientRoomCollection);
        System.out.println(allClients_);
    }
}
