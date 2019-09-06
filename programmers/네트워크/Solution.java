import java.util.Arrays;

class Solution {

  private void dfs(int n, int node, int[][] computers, boolean[] visited) {
    if(visited[node]) {
      return;
    }

    visited[node] = true;
    for(int i = 0; i < n; i++) {
      if(i != node && computers[node][i] == 1) {
        if(!visited[i]) {
          dfs(n, i, computers, visited);
        }
      }
    }
  }

  public int solution(int n, int[][] computers) {
    int answer = 0;

    boolean[] visited = new boolean[n];
    Arrays.fill(visited, false);

    for(int i = 0; i < n; i++) {
      if(!visited[i]) {
        answer++;
        dfs(n, i, computers, visited);
      }
    }
    
    return answer;
  }
}