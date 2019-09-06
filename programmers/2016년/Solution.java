class Solution {
  public String solution(int a, int b) {
    String answer = "";

    final int[] daysOfMonth = new int[] {
      0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    final String[] dayNames = new String[] {
      "THU", "FRI", "SAT", "SUN", "MON", "TUE", "WED"
    };
    
    int days = 0;
    for(int m = 1; m < a; m++) {
      days += daysOfMonth[m];
    }
    days += b; 
    
    days %= 7;
    answer = dayNames[days];

    return answer;
  }
}