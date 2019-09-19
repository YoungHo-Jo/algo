import java.util.Arrays;
import java.util.Collections;
import java.util.stream.Collectors;
import java.util.ArrayList;

class Solution {
  private String make4Digits(String str) {
    if(str.length() < 4) {
      StringBuilder sb = new StringBuilder(str);
      while(sb.length() < 4) {
        sb.append("0");
      }

      return sb.toString();
    }

    return str;
  }

  public String solution(int[] numbers) {
    String answer = "";

    ArrayList<String> strNumbers = Arrays.stream(numbers)
      .mapToObj(i -> String.valueOf(i))
      .sorted((lhs, rhs) -> {
        String tempLhs = make4Digits(lhs);
        String tempRhs = make4Digits(rhs);

        int compareResult = tempLhs.compareTo(tempRhs);

        return compareResult == 0 ? rhs.length() - lhs.length() : compareResult;

      })
      .collect(ArrayList::new, ArrayList::add, ArrayList::addAll);

    Collections.reverse(strNumbers);
      
    answer = strNumbers.stream()
      .filter(s -> Integer.parseInt(s) != 0)
      .collect(Collectors.joining(""));

    if(answer.equals("")) {
      answer = "0";
    }


    return answer;
  }
}