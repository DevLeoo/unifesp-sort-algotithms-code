import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SelectionSort {

    public static void main(String[] args) {
        long startTime = System.nanoTime();

        int[] data =  SelectionSort.readCSV();
        selectionSort(data); 
        
        long endTime = System.nanoTime();
        long executionTime = endTime - startTime;

        System.out.println("Execution time: " + (executionTime / 1_000_000) + " ms");

        // System.out.println("Sorted Array:");
        // for (int num : data) {
        //     System.out.print(num + " ");
        // }
    }

    public static void selectionSort(int[] data) {
        int n = data.length;

        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[minIndex]) {
                    minIndex = j;
                }
            }

            int temp = data[minIndex];
            data[minIndex] = data[i];
            data[i] = temp;
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