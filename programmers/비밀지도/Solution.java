class Solution {
  public String[] solution(int n, int[] arr1, int[] arr2) {
    String[] answer = new String[n];

    int[] map = new int[n];
    for(int i = 0; i < n; i++) {
      map[i] = arr1[i] | arr2[i];
    }

    for(int i = 0; i < n; i++) {
      StringBuilder sb = new StringBuilder();
      int bitIdx = 1 << (n - 1);
      for(int b = 0; b < n; b++) {
        if((map[i] & bitIdx >> b) == 0) {
          sb.append(" ");
        } else {
          sb.append("#");
        }
      }
      
      answer[i] = sb.toString();
    }

    return answer;
  }
}