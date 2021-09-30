import java.util.Random;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello World!");

        int [] intArray = new int[10];

        for(int i = 0; i < 10; i++) {
            Random rand = new Random();
            intArray[i] = rand.nextInt();
            System.out.println(i + ": " + intArray[i]);
        }

        /// Part 1:
        // Variables
        int userAge;
        int votingAge = 21;
        int senateAge = 25;

        // Ask user for their age
        System.out.println("Kindly enter your age below: ");
        Scanner s = new Scanner(System.in);
        userAge = s.nextInt();

        // Logic and Output
        if (userAge >= votingAge) {
            System.out.println("You are old enough to vote!");
        } else {
            System.out.println("You are not old enough to vote!");
        }
        if (userAge >= senateAge) {
            System.out.println("You are old enough to run for the Senate!");
        } else {
            System.out.println("You are not old enough to run for the Senate!");
        }

        if (userAge >= 80) {
            System.out.println("You are a part of the greatest generation!");
        } else if (userAge >= 60) {
            System.out.println("You are a part of the baby boomer!");
        } else if (userAge >= 40) {
            System.out.println("You are a part of the generation!");
        } else if (userAge >= 20) {
            System.out.println("You are a part of the millennial!");
        } else {
            System.out.println("You are a part of the iKid!");
        }

        /// Part 2
        // Variables
        char weekday;
        char holiday;
        char youngChildren;
        boolean isWeekday = false;
        boolean isHoliday = false;
        boolean isYoungChildren = false;

        // Ask user for their age
        s = new Scanner(System.in);
        System.out.println("Kindly enter Y or N based on if it is a weekday or not:");
        weekday = s.next().charAt(0);

        s = new Scanner(System.in);
        System.out.println("Kindly enter Y or N based on if it is a holiday or not:");
        holiday = s.next().charAt(0);

        s = new Scanner(System.in);
        System.out.println("Kindly enter Y or N based on if you have children or not:");
        youngChildren = s.next().charAt(0);

        // Logic and Output
        if (weekday == 'Y'|| weekday == 'y') {
            isWeekday = true;
        } else if (weekday == 'N'|| weekday == 'n') {
            isWeekday = false;
        } else {
            System.out.println("Invalid Response! Restart the program!");
            System.exit(1);
        }

        if (holiday == 'Y'|| holiday == 'y') {
            isHoliday = true;
        } else if (holiday == 'N'|| holiday == 'n'){
            isHoliday = false;
        } else {
            System.out.println("Invalid Response! Restart the program!");
            System.exit(1);
        }

        if (youngChildren == 'Y'|| youngChildren == 'y') {
            isYoungChildren = true;
        } else if (youngChildren == 'N'|| youngChildren == 'n'){
            isYoungChildren = false;
        } else {
            System.out.println("Invalid Response! Restart the program!");
            System.exit(1);
        }

        if (isYoungChildren) {
            System.out.println("You cannot sleep in today :(");
        } else if (isHoliday || !isWeekday) {
            System.out.println("You can sleep in today :)");
        } else {
            System.out.println("You cannot sleep in today :)");
        }
    }
}
