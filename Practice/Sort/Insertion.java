import java.util.Arrays;
import java.util.stream.Collectors;

class Insertion {

  static void sort(int[] arr) {
    for(int i = 0; i < arr.length; i++) {
      for(int j = i; j >= 1; j--) {
        if(arr[j] < arr[j - 1]) {
          swap(arr, j, j - 1);
        }
      }      
    }
  }

  static void swap(int[] arr, int lhs, int rhs) {
    if(lhs < 0 || rhs < 0 || lhs >= arr.length || rhs >= arr.length) {
      throw new IndexOutOfBoundsException();
    }

    int temp = arr[lhs];
    arr[lhs] = arr[rhs];
    arr[rhs] = temp;
  }

  public static void main(String[] args) {
    int[] arr = {
      10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    };

    print(arr);
    sort(arr);
    print(arr);
    
  }

  public static void print(int[] arr) {
    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < arr.length; i++) {
      sb.append(arr[i]);
      sb.append(" ");
    }

    System.out.println(sb.toString());
  }

}