import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class CountingSort {

    public static void main(String[] args) {
        long startTime = System.nanoTime();

        int[] data = CountingSort.readCSV();

        long endTime = System.nanoTime();
        long executionTime = endTime - startTime;

        System.out.println("Execution time: " + (executionTime / 1_000_000) + " ms");

        countingSort(data);

        // for (int num : data) {
        //     System.out.print(num + " ");
        // }
    }

    public static void countingSort(int[] data) {
        int max = Arrays.stream(data).max().getAsInt();
        int min = Arrays.stream(data).min().getAsInt();
        int range = max - min + 1;

        int[] count = new int[range];
        int[] output = new int[data.length];

        for (int i = 0; i < data.length; i++) {
            count[data[i] - min]++;
        }

        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        for (int i = data.length - 1; i >= 0; i--) {
            output[count[data[i] - min] - 1] = data[i];
            count[data[i] - min]--;
        }

        for (int i = 0; i < data.length; i++) {
            data[i] = output[i];
        }
    }

    public static int[] readCSV() {
        String file = "./../cenarios/1000000qo.csv";
        
        List<Integer> secondElements = new ArrayList<>();
        
        String delimiter = ",";
        String line;
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            while ((line = br.readLine()) != null) {
                List<String> values = Arrays.asList(line.split(delimiter));
                if (values.size() >= 2) {
                    int secondElement = Integer.parseInt(values.get(1));
                    secondElements.add(secondElement);
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        }
        
        int[] response = secondElements.stream()
                .mapToInt(Integer::intValue)
                .toArray();

        // for (int element : response) {
        //     System.out.println(element);
        // }
        
        return response;
    }
}