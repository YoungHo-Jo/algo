class Selection {
  
  static void sort(int[] arr) {

    for(int i = 0; i < arr.length; i++) {
      int minIndex = i;
      for(int j = i + 1; j < arr.length; j++) {
        if(arr[j] < arr[minIndex])  {
          minIndex = j;
        }
      }

      swap(arr, minIndex, i);
    }
  }

  static void swap(int[] arr, int lhs, int rhs) {
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

  static void print(int[] arr) {
    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < arr.length; i++) {
      sb.append(arr[i]);
      sb.append(" ");
    }

    System.out.println(sb.toString());
  }
}