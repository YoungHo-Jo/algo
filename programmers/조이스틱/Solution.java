import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.IntStream;

class Solution {

  private static final String ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  private int distance(int total, int from, int to) {
    if(from <= to) {
      return to - from;
    } else {
      return to + total - from;
    }
  }

  public int solution(String name) {
    int answer = 0;
    int len = name.length();

    char[] base = new char[len];
    char[] nameCharArray = name.toCharArray();
    Arrays.fill(base, 'A');

    int pointer = len;
    
    while(true) {
      
      for(int i = 1; i < len; i++) {
        int lhs = (pointer - i)%len;
        int rhs = (pointer + i)%lhs;
        
      }


      if(closest == name.length()) {
        break;
      }

    }

    return answer;
  }



}