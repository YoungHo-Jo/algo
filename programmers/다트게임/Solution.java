import java.util.ArrayList;
import java.util.Arrays;

class Solution {
  public int solution(String dartResult) {
    int answer = 0;
  
    ArrayList<Integer> scores = new ArrayList<>();

    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < dartResult.length(); i++) {
      char c = dartResult.charAt(i);
      int lastIndex = scores.size() - 1;

      if(c == 'S' || c == 'D' || c == 'T') {
        Integer score = Integer.valueOf(sb.toString());
        sb = new StringBuilder();
        if(c == 'D') {
          score = (int)Math.pow(score, 2);
        } else if(c == 'T') {
          score = (int)Math.pow(score, 3);
        }
        scores.add(score);
      } else if(c == '*') {
        scores.set(lastIndex, scores.get(lastIndex)*2);
        if(lastIndex != 0) {
          scores.set(lastIndex  - 1, scores.get(lastIndex - 1)*2);
        }
      } else if(c == '#') {
        scores.set(lastIndex, scores.get(lastIndex)*(-1));
      } else {
        sb.append(c);
      }
    }

    answer = scores
      .stream()
      .reduce((s1, s2) -> s1 + s2)
      .get().intValue();
    return answer;
  }
}