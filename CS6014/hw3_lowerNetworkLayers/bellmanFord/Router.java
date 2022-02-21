package msd.benjones;

import java.util.HashMap;
import java.util.Set;

public class Router {

    private HashMap<Router, Integer> distances;
    private String name;

    public Router(String name) {
        this.distances = new HashMap<>();
        this.name = name;
    }

    public void onInit() throws InterruptedException {

        for (Neighbor neighbor : Network.getNeighbors(this)) {

            this.distances.put(neighbor.router, neighbor.cost); // Initiate distance table

        }

        for (Neighbor neighbor : Network.getNeighbors(this)) {

            Network.sendDistanceMessage(new Message(this, neighbor.router, this.distances)); // Broadcast to neighbors

        }
    }

    public void onDistanceMessage(Message message) throws InterruptedException {
        boolean isChanged = false;
        int distanceToSender = this.distances.get(message.sender);

        for (Neighbor neighbor : Network.getNeighbors(this)) {
            Integer distanceFromSenderToNeighbor = message.distances.get(neighbor.router);

            if (distanceFromSenderToNeighbor == null) {
                continue;
            }

            int distanceToNeighborThroughSender = distanceToSender + distanceFromSenderToNeighbor;

            if (distanceToNeighborThroughSender < this.distances.get(neighbor.router)) {
                isChanged = true;
                this.distances.put(neighbor.router, distanceToNeighborThroughSender);
            }
        }

        if (isChanged) {
            for (Neighbor neighbor : Network.getNeighbors(this)) {
                Network.sendDistanceMessage(new Message(this, neighbor.router, distances));
            }
        }


    }


    public void dumpDistanceTable() {
        System.out.println("router: " + this);
        for (Router r : distances.keySet()) {
            System.out.println("\t" + r + "\t" + distances.get(r));
        }
    }

    @Override
    public String toString() {
        return "Router: " + name;
    }
}
