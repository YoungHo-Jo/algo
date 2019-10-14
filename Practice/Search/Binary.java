class Binary {

  public static void main(String[] args) {
    int[] arr = {
      1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    print(arr);
    boolean result = search(arr, 0);

    System.out.println(result ? "found" : "not found");

  }

  static boolean search(int[] arr, int target) {
    int lhs = 0;
    int rhs = arr.length - 1; 

    while(lhs < rhs) {
      int mid = (lhs + rhs)/2;
      
      if(arr[mid] == target) {
        return true;
      }

      if(target < arr[mid]) {
        rhs = mid; 
      } else {
        lhs = mid + 1;
      }
    }

    return false;
  }

  

  static void print(int[] arr) {
    StringBuilder sb = new StringBuilder();
    for(int i: arr) {
      sb.append(i);
      sb.append(" ");
    }

    System.out.println(sb.toString());
  }
}