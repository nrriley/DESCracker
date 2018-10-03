import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class convert {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new FileInputStream("sboxes.txt"));
        int stables[][][] = new int[8][4][16];
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 16; k++)
                    stables[i][j][k] = in.nextInt();
        System.out.print("{");
        for (int i = 0; i < 8; i++) {
          System.out.print("{");
            for (int j = 0; j < 4; j++) {
                String derp = Arrays.toString(stables[i][j]).replaceAll("\\[", "\\{").replaceAll("\\]", "\\}");
                System.out.print(derp);

                System.out.println();
               
            }
            if(i == 7)
                System.out.print("}");
            else
                System.out.print("},");
            System.out.println();
        }
        System.out.print("}");
        System.out.println();
        in.close();
    }
}