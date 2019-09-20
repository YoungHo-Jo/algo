import java.util.Arrays;
import java.util.Deque;
import java.util.ArrayDeque;


class Solution {
  public int solution(int n, int[][] edge) {
    int answer = 0;

    boolean[] visited = new boolean[edge.length];
    int[] length = new int[n + 1];
 
    Arrays.fill(visited, false);
    Arrays.fill(length, -1);
    
    Deque<Integer> bfsQueue = new ArrayDeque<>();
    Deque<Integer> distQueue = new ArrayDeque<>();
    length[1] = 0;
    bfsQueue.add(1);
    distQueue.add(0);
    while(bfsQueue.isEmpty() == false) {
      Integer here = bfsQueue.getFirst();
      Integer dist = distQueue.getFirst();
     
      for(int i = 0; i < edge.length; i++) {
        if(visited[i]) continue;

        int[] e = edge[i];
        int to = -1;
        int lhs = e[0];
        int rhs = e[1];
        if(lhs == here) {
          to = rhs;
        } else if(rhs == here) {
          to = lhs;
        }

        if(to != -1 && length[to] == -1) {
          visited[i] = true;
          length[to] = dist + 1;
          bfsQueue.addLast(to);
          distQueue.addLast(dist + 1);
        }

      }

      bfsQueue.removeFirst();
      distQueue.removeFirst();

    }

    int max = Arrays.stream(length)
      .max().getAsInt();

    answer = (int) Arrays.stream(length)
      .filter(i -> i == max)
      .count();

    return answer;
  }
}