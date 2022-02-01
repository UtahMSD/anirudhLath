import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class Parser {
    public static void main(String[] args) throws IOException {
        Parser traceroute = new Parser("tracert.txt");
        Parser tracerouteAfter = new Parser("tracert2.txt");
        Parser ping = new Parser("ping.txt");

        ping.parsePing("pingResults.txt");
        traceroute.parseTrace("traceResults.csv");
        tracerouteAfter.parseTrace("traceResultsAfter.csv");
    }
    private Scanner scanner;
    private FileWriter writer;

    public Parser(String filename) throws FileNotFoundException {
        scanner = new Scanner(new File(filename));
    }

    public void parseTrace(String filename) throws IOException {
        writer = new FileWriter(new File(filename), false);
        while(scanner.hasNextLine()) {
            String[] temp = scanner.nextLine().split(" ");
            //System.out.println(Arrays.deepToString(temp));

            String ipAddress = null;
            for(String str : temp) {
                try {
                    if(str.charAt(0) == '(') {
                        ipAddress = str.substring(1,str.length() - 1);
                        break;
                    }
                } catch (Exception e) {
                }
            }

            if(ipAddress == null) {
                continue;
            }

            float totalRtt = 0.0f;
            int rttCount = 0;
            for(int i = 2; i < temp.length; i++) {
                try {
                    totalRtt += Float.parseFloat(temp[i]);
                    rttCount++;
                } catch (NumberFormatException e) {

                }
            }
            writer.write(ipAddress + ',' + totalRtt/rttCount + '\n');
        }
        writer.close();
    }

    public void parsePing(String filename) throws IOException {
        writer = new FileWriter(new File(filename), false);
        int count = 0;
        float totalTime = 0.0f;
        float min = 0.0f;
        while(scanner.hasNextLine()) {
            String[] temp = scanner.nextLine().split(" ");
            System.out.println(Arrays.deepToString(temp));
            if(temp.length == 8) {
                totalTime += Float.parseFloat(temp[6].substring(5));
                count++;
            }
            if(temp.length == 5) {
                if(temp[0].equals("round-trip")) {
                    String[] arr = temp[3].split("/");
                    min = Float.parseFloat(arr[0]);
                }
            }
        }
        writer.write("Minimum Delay: " + min + '\n');
        writer.write("Total packets: " + count + '\n');
        writer.write("Average Queuing Delay: " + (totalTime - (min * count)) / count + '\n');
        writer.close();
    }
}
