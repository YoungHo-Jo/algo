import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.lang.Character;
import java.io.FileInputStream;

class Solution {
	public static void main(String args[]) throws Exception {
		Scanner sc = new Scanner(System.in);
    int T = Integer.parseInt(sc.nextLine());
  
		for(int test_case = 1; test_case <= T; test_case++) {
      String[] tokens = sc.nextLine().split(" ");
      int n = Integer.parseInt(tokens[0]);
      int k = Integer.parseInt(tokens[1]);
      String line = sc.nextLine();
      
      ArrayDeque<Character> deq = new ArrayDeque<>();
      for(int i = 0; i < line.length(); i++) {
        deq.add(line.charAt(i));
      }

      ArrayList<Integer> nums = new ArrayList<>();

      for(int i = 0; i < n; i++) {
        nums.addAll(getNums(n, deq));
        
        deq.add(deq.getFirst());
        deq.removeFirst();
      }

      nums.sort(Comparator.reverseOrder());

      
      int ans = 0;
      int prev = nums.get(0);
      int idx = 0;
      for(int i = 1; i < nums.size(); i++) {
        if(prev != nums.get(i)) {
          idx++;
          prev = nums.get(i);
        } 

        if(idx == k - 1) {
          ans = prev;
          break;
        }
      }

      System.out.println("#" + test_case + " " + ans);
    }
    
    
  }

  
  static ArrayList<Integer> getNums(int n, ArrayDeque<Character> deque) {
    final int sideCnt = n/4;

    int cnt = 0;
    String temp = "";
    ArrayList<Integer> result = new ArrayList<>();

    for(int i = 0; i < n; i++) {
      Character c = deque.getFirst();
      deque.removeFirst();
      deque.addLast(c);

      temp = temp + c;

      cnt++;
      if(cnt == sideCnt) {
        // string to int

        int num = Integer.valueOf(temp, 16);
        result.add(num); 
        temp = "";
        cnt = 0;
      }
    }

    return result;
  } 
}