import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FlightTester {
    static Scanner inFile = null;

    public static void main(String[] args) {
        // make the flight plan array
        boolean[][] flightPlan = new boolean[7][7];

        // fill the true
        flightPlan[1][2]=true;
        flightPlan[1][3]=true;
        flightPlan[1][6]=true;
        flightPlan[2][1]=true;
        flightPlan[2][3]=true;
        flightPlan[2][6]=true;
        flightPlan[3][4]=true;
        flightPlan[4][2]=true;
        flightPlan[4][5]=true;
        flightPlan[4][6]=true;
        flightPlan[5][2]=true;
        flightPlan[5][4]=true;
        flightPlan[6][2]=true;
        flightPlan[6][5]=true;

        // read for file
        try {
            // create scanner to read file
            inFile = new Scanner(new File ("prog475a.dat"));
        } catch (FileNotFoundException e) {
            System.out.println("File not found!");
            System.exit(0);
        }

        /*
         * read customer number
         * method to translate flight plan into coordinates
         * 
         */

        int customer = 0;
        int flight = 0;

        while (inFile.hasNext()) {
            customer = inFile.nextInt();
            flight = inFile.nextInt();
            translator(customer, flight, flightPlan);
        }
    }

    public static void translator(int c, int f, boolean[][] fl) {
        System.out.println("Customer Number " + c + "    Flight Plan " + f);
        int[] coo = new int[5];

        int a = 10000;

        for (int x = 0; x < coo.length; x++) {
            coo[x] = (f / a) % 10;
            a /= 10;    
        }

        for (int x = 0; x < coo.length - 1; x++) {
            int p = coo[x]; 
            int q = coo[x + 1];

            if (fl[p][q]) {
                System.out.print(p + "\t" + q + "\tAvailable");

                if (x == coo.length - 2) {
                    System.out.println("\tFlight Plan is Valid");
                }
                else {
                    System.out.println("");
                }
            }
            else {
                System.out.println(p + "\t" + q + "\tUnavailable\tFlight Plan is Invalid");
                break;
            }
        }
    }
}
