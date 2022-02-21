package msd.benjones;

import msd.benjones.VisualizationHelper.RecordData;

import java.io.IOException;

public class Main {

    public static void main(String[] args) throws InterruptedException, IOException {

        //Network.makeSimpleNetwork(); //use this for testing/debugging
        int[] sizes = new int[]{10,20,30,40,50};
        plotter(sizes); // Algorithms in this function for reliable data collection

        Network.dump();

        Network.startup();
        Network.runBellmanFord();

        System.out.println("done building tables!");
        for(Router r : Network.getRouters()){
            r.dumpDistanceTable();
        }
        System.out.println("total messages: " + Network.getMessageCount());


    }

    private static void plotter(int[] sizes) throws IOException, InterruptedException {
        RecordData file = new RecordData("Plottings.csv");
        for (int j = 0; j < sizes.length; j++) {
            int sum = 0;
            int runs = 1000;

            for(int i = 0; i < runs; i++) {
                Network.makeProbablisticNetwork(sizes[j]); //use this for the plotting part
                Network.dump();

                Network.startup();
                Network.runBellmanFord();
                for(Router r : Network.getRouters()){
                    r.dumpDistanceTable();
                }
                sum += Network.getMessageCount();
            }

            int avg = sum / runs;

            file.writeData(sizes[j], avg);
        }
        file.closeFile();
    }
}
