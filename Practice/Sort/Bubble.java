class Bubble {

  
  public static void main(String[] args) {
    int[] array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    System.out.println("before sort");
    printArray(array);

    System.out.println("after sort");
    bubbleSort(array);
    printArray(array);
  }

  static void bubbleSort(int[] array) {
    for(int i = 0; i < array.length; i++) {
      for(int j = i + 1; j < array.length; j++) {
        if(array[i] > array[j]) {
          int temp = array[j];
          array[j] = array[i];
          array[i] = temp;
        }
      }
    }
  }

  static void printArray(int[] array) {
    StringBuilder sb = new StringBuilder();

    for(int i = 0; i < array.length; i++) {
      sb.append(array[i]);
      sb.append(", ");
    } 

    System.out.println(sb.toString());
  }

}