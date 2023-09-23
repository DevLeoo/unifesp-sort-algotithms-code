import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class QuickSort {

    public static void main(String[] args) {
        long startTime = System.nanoTime();

        int[] data = QuickSort.readCSV();
        quickSort(data, 0, data.length - 1);

        long endTime = System.nanoTime();
        long executionTime = endTime - startTime;

        System.out.println("Execution time: " + (executionTime / 1_000_000) + " ms");
       
        // for (int num : data) {
        //     System.out.print(num + " ");
        // }
    }

    public static void quickSort(int[] data, int low, int high) {
        if (low < high) {
            int partitionIndex = partition(data, low, high);

            quickSort(data, low, partitionIndex - 1);
            quickSort(data, partitionIndex + 1, high);
        }
    }

    public static int partition(int[] data, int low, int high) {
        int pivot = data[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (data[j] < pivot) {
                i++;

                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }

        int temp = data[i + 1];
        data[i + 1] = data[high];
        data[high] = temp;

        return i + 1;
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
