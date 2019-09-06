import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.text.SimpleDateFormat;
import java.util.Date;


class Solution {
  class Pair {
    public long lhs, rhs;
    public Pair(long _lhs, long _rhs) {
      this.lhs = _lhs;
      this.rhs = _rhs; 
    }

    boolean inRange(long x) {
      return lhs <= x && x <= rhs;      
    }

    // boolean inRange(Pair p) {
    //   return inRange(p.lhs) || inRange(p.rhs);
    // }

    boolean inRange(Pair p) {
      if(rhs < p.lhs || lhs >= p.rhs) return false;
      return true;  
    }
  }


  public int solution(String[] lines) {
    int answer = 0;

    ArrayList<Pair> reqs = new ArrayList<>(lines.length);
    for(String line: lines) {
      String[] tokens = line.split(" ");
      double[] endTimeToken = Arrays
        .stream(tokens[1].split(":"))
        .mapToDouble(s -> Double.parseDouble(s)*1000)
        .toArray();
      long endTime = (long)((endTimeToken[0] * 3600 + endTimeToken[1] * 60 + endTimeToken[2]));
      long startTime = endTime - (long)(Double.parseDouble(
        tokens[2].substring(0, tokens[2].length() - 1)
      )*1000) + 1 ;

      reqs.add(new Pair(startTime, endTime));

      // reqs.add(parse(line));
    }
    
    for(int i = 0; i < reqs.size(); i++) {
      Pair p = reqs.get(i);
      int cntLhs = 0, cntRhs = 0;
      Pair lhsBlock = new Pair(p.lhs, p.lhs + 1000);
      Pair rhsBlock = new Pair(p.rhs, p.rhs + 1000);

      for(int j = 0; j < reqs.size(); j++) {
        Pair tempP = reqs.get(j);
        if(tempP.inRange(lhsBlock)) {
          cntLhs++;
        }

        if(tempP.inRange(rhsBlock)) {
          cntRhs++;
        }
      } 

      answer = Math.max(Math.max(cntLhs, cntRhs), answer);
    }

    return answer;
  }

  // Pair parse(String line) {
  //   String[] split = line.split(" ");
  //   String dateString = split[0] + " " + split[1];
  //   try {
  //     Date startDate = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS").parse(dateString);
  //     long end = startDate.getTime();

  //     String[] split2 = split[2].split("s");
  //     double parseDouble = Double.parseDouble(split2[0]);
  //     long duration = (long) (parseDouble * 1000);

  //     long start = end - duration; 
  //     return new Pair(start, end);
  //   } catch (Exception e) {
  //     e.printStackTrace();
  //     return null;
  //   }
  // }
}