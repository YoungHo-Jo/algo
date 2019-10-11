import java.util.Arrays;
import java.util.stream.Collectors;

class Quick {

  public static void main(String[] args) {
    int[] arr = {
      10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    };

    print(arr);
    sort(arr);
    print(arr);
  }

  static void sort(int[] arr) {
    sort(arr, 0, arr.length - 1);
  }

  private static void sort(int[] arr, int first, int last) {
    if(first >= last) return;
    int pivot = (first + last)/2;
    swap(arr, first, pivot);
    pivot = first;
    int lhs = first;
    int rhs = last;
    while(lhs < rhs) {
      while(arr[lhs] <= arr[pivot] && lhs < last) {
        lhs++;
      }
      while(arr[rhs] > arr[pivot]) {
        rhs--;
      }

      if(lhs < rhs) {
        swap(arr, lhs, rhs);
      }
    }

    swap(arr, pivot, rhs);
    sort(arr, first, rhs - 1);
    sort(arr, rhs + 1, last);
  }

  private static void swap(int[] arr, int lhs, int rhs) {
    int temp = arr[lhs];
    arr[lhs] = arr[rhs];
    arr[rhs] = temp;
  }
  
  static void print(int[] arr) {
    StringBuilder sb = new StringBuilder();

    for(int i = 0; i < arr.length; i++) {
      sb.append(arr[i]);
      sb.append(" ");
    }

    System.out.println(sb.toString());
  }
}