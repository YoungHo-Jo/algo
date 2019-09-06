import java.util.ArrayList;
import java.util.Arrays;

class Solution {
  public int[] solution(int[] answers) {
      int[] answer = {};

      ArrayList<int[]> patterns = new ArrayList<>(3);
      patterns.add(new int[]{1, 2, 3, 4, 5});
      patterns.add(new int[]{2, 1, 2, 3, 2, 4, 2, 5});
      patterns.add(new int[]{3, 3, 1, 1, 2, 2, 4, 4, 5, 5});

      int[] scores = new int[3];
      Arrays.fill(scores, 0);      
      
      int maxScore = 0;
      for(int i = 0; i < answers.length; i++) {
        for(int j = 0; j < 3; j++) {
          int[] pattern = patterns.get(j);
          scores[j] += answers[i] == pattern[(i % pattern.length)] ? 1 : 0;
          if(scores[j] > maxScore) {
            maxScore = scores[j];
          }
        }
      }
        
      ArrayList<Integer> result = new ArrayList<>();
      for(int i = 0; i < 3; i++) {
        if(maxScore == scores[i]) {
          result.add(i + 1);
        }
      }
      
      return result.stream().mapToInt(i -> i.intValue()).toArray();
  }
}