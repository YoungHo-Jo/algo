
class Merge {

  public static void main(String[] args) {
    int[] arr = {
      10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    };

    print(arr);
    sort(arr);
    print(arr); 

  }

  static void sort(int[] arr) {
    int[] result = sort(arr, 0, arr.length - 1);     
    for(int i = 0; i < result.length; i++) {
      arr[i] = result[i];
    }
  }

  static int[] sort(int[] arr, int start, int end) {
    if(start > end) return null;
    
    if(start == end) {
      int[] temp = new int[1];
      temp[0] = arr[start];
      return temp;
    }

    
    int[] temp = new int[end - start + 1];
    
    int mid = (start + end)/2;

    int[] lhs = sort(arr, start, mid);
    int[] rhs = sort(arr, mid + 1, end);

    if(lhs == null) return rhs;
    else if(rhs == null) return lhs;

    int lhsPointer = 0;
    int rhsPointer = 0;
    for(int i = 0; i < temp.length; i++) {
      if(lhsPointer >= lhs.length) {
        temp[i] = rhs[rhsPointer];
        rhsPointer++;
      } else if(rhsPointer >= rhs.length) {
        temp[i] = lhs[lhsPointer];
        lhsPointer++;
      } else {
        if(lhs[lhsPointer] < rhs[rhsPointer]) {
          temp[i] = lhs[lhsPointer];
          lhsPointer++;
        } else {
          temp[i] = rhs[rhsPointer];
          rhsPointer++;
        }
      }
    }

    return temp;
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