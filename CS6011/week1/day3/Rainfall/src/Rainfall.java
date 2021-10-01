import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Rainfall {
    class rainData {
        String month;
        int year;
        double rainScale;

        public rainData()
        {
            month = "";
            year = 0;
            rainScale = 0.0;
        }
    }
    class cities {
        ArrayList<rainData> rainDatas;
        String name;

        public cities()
        {
            rainDatas = new ArrayList<>();
            name = "";

        }
    }

    public cities readData(File myStream) throws FileNotFoundException {
        String cityName;
        cities city = new cities();
        Scanner fileReader = new Scanner(myStream);
        cityName = fileReader.next();
        city.name = cityName;
        for(int i = 0; i < 240; i++) {
            rainData rainData = new rainData();
            rainData.month = fileReader.next();
            rainData.year = fileReader.nextInt();
            rainData.rainScale = fileReader.nextFloat();
            city.rainDatas.add(rainData);
            System.out.println(rainData.month + " " + rainData.year + " " + rainData.rainScale);
        }
        return city;
    }

    double averageRainfall(String month, cities city){
        double average = 0;
        double sum = 0;
        int count = 0;
        for(rainData rainDataMonth: city.rainDatas) {
            if(rainDataMonth.month.equals(month)){
                sum += rainDataMonth.rainScale;
                count++;
            }
        }
        average = sum / count;
        return average;
    }

    void sortRainData(cities city){
        for (int i = 0; i < city.rainDatas.size(); i++) {
            for (int x = 0; x < city.rainDatas.size(); x++) {
                if(city.rainDatas.get(i).rainScale < city.rainDatas.get(x).rainScale) {
                    rainData temp = city.rainDatas.get(i);
                    city.rainDatas.set(i, city.rainDatas.get(x));
                    city.rainDatas.set(x,temp);
                }
            }
        }
    }

    ArrayList<Double> fourWettestMonths(cities city){
        ArrayList<Double> wettestMonths = new ArrayList<>();
        sortRainData(city);
        for (int i = city.rainDatas.size() - 1; i > city.rainDatas.size() - 5; i--) {
            wettestMonths.add(city.rainDatas.get(i).rainScale);
        }
        return wettestMonths;
    }

    ArrayList<Double> fourDriestMonths(cities city){
        ArrayList<Double> driestMonths = new ArrayList<>();
        sortRainData(city);
        for (int i = 0; i < 4; i++) {
            driestMonths.add(city.rainDatas.get(i).rainScale);
        }
        return driestMonths;
    }

    rainData medianRain(cities city){
        sortRainData(city);
        double medianIndex;
        if(city.rainDatas.size() % 2 == 0){
            medianIndex = (city.rainDatas.size() + 1) / 2;
        } else {
            medianIndex = city.rainDatas.size() / 2;
        }
        rainData rainData = city.rainDatas.get((int) medianIndex);
        return rainData;
    }

    public void writeData(File myStream, ArrayList<cities> vectorOfCities) throws IOException
    {
        PrintWriter writer = new PrintWriter(myStream);
        writer.println("CS 6010 Rainfall Analysis");
        for(cities city: vectorOfCities){
            writer.println("Rainfall data for " + city.name + "\n");
            writer.println("The average rainfall amount for January is " + averageRainfall("January", city) + " inches.");
            writer.println("The average rainfall amount for February is " + averageRainfall("February", city) + " inches.");
            writer.println("The average rainfall amount for March is " + averageRainfall("March", city) + " inches.");
            writer.println("The average rainfall amount for April is " + averageRainfall("April", city) + " inches.");
            writer.println("The average rainfall amount for May is " + averageRainfall("May", city) + " inches.");
            writer.println("The average rainfall amount for June is " + averageRainfall("June", city) + " inches.");
            writer.println("The average rainfall amount for July is " + averageRainfall("July", city) + " inches.");
            writer.println("The average rainfall amount for August is " + averageRainfall("August", city) + " inches.");
            writer.println("The average rainfall amount for September is " + averageRainfall("September", city) + " inches.");
            writer.println("The average rainfall amount for October is " + averageRainfall("October", city) + " inches.");
            writer.println("The average rainfall amount for November is " + averageRainfall("November", city) + " inches.");
            writer.println("The average rainfall amount for December is " + averageRainfall("December", city) + " inches.");

            // Wettest Months
            writer.printf("The rain amount (in inches) of the four wettest months is: ");
            ArrayList<Double> wettestMonths = fourWettestMonths(city);
            for (double data: wettestMonths) {
                writer.printf( data + " ");
            }
            writer.println();

            // Driest Months
            writer.printf("The rain amount (in inches) of the four driest months is: ");
            ArrayList<Double> driestMonths = fourDriestMonths(city);
            for (double data: driestMonths) {
                writer.printf(data + " ");
            }
           writer.println("\n");

            //Median Month
            writer.println("The median month is:");
            rainData median = medianRain(city);
            writer.println(median.month + " " + median.year + " " + median.rainScale);
        }
        writer.close();
    }

    public Rainfall()
    {
        rainData rainData;
        cities city;
    }

    public static void main(String[] args) throws IOException {

        File inputAtlanta = new File("Day3_Atlanta.txt");
        File inputMacon = new File("Day3_Macon.txt");
        File output = new File("rainfall_results.txt");

        Rainfall rainfall = new Rainfall();

        cities atlanta = rainfall.readData(inputAtlanta);
        cities macon = rainfall.readData(inputMacon);

        ArrayList<cities> vectorOfCities = new ArrayList<>();
        vectorOfCities.add(atlanta);
        //vectorOfCities.add(macon);

        rainfall.writeData(output, vectorOfCities);



    }
}