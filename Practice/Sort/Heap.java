
class Heap {

  public static void main(String[] args) {
    int[] arr = {
      10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    };

    print(arr);
    sort(arr);
    print(arr);
  }

  static void print(int[] arr) {
    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < arr.length; i++) {
      sb.append(arr[i]);
      sb.append(" ");
    }

    System.out.println(sb.toString());
  }

  static void sort(int[] arr) {
    for(int i = arr.length - 1; i >= 0; i--) {
      sort(arr, i, arr.length);
    }
    
    for(int i = arr.length - 1; i >= 0; i--) {
      swap(arr, 0, i);
      sort(arr, 0, i);
    }
  }

  private static void sort(int[] arr, int top, int len) {
    int lhs = top*2 + 1;
    int rhs = top*2 + 2;
   
    int largest = top;
    if(lhs < len && arr[largest] < arr[lhs]) {
      largest = lhs;
    } 

    if(rhs < len && arr[largest] < arr[rhs]) { 
      largest = rhs;
    }

    if(largest != top) {
      swap(arr, largest, top);
      sort(arr, largest, len);
    }
  }

  private static void swap(int[] arr, int lhs, int rhs) {
    int temp = arr[lhs];
    arr[lhs] = arr[rhs];
    arr[rhs] = temp;
  }
}