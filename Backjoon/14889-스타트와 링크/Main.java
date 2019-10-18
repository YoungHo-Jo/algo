/*
  start: 2019.10.18 17:00
  end: 2019.10.18 17:39
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.BitSet;
import java.util.StringTokenizer;
import java.util.stream.Collector;
import java.util.stream.Collectors;

class Main {

  static int[][] scores = new int[20][20];
  static int N;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    
    N = Integer.parseInt(br.readLine());
    
    for(int i = 0; i < N; i++) {
      scores[i] = new int[20];
    
      StringTokenizer stringTokenizer = new StringTokenizer(br.readLine());
      int j = 0;
      while(stringTokenizer.hasMoreTokens()) {
        scores[i][j++] = Integer.parseInt(stringTokenizer.nextToken());
      }
    }

    int ans = solve(new int[20], 0, 0);

    System.out.println(ans);
  }

  static int solve(int[] teamA, int n, int curIndex) {
    if(n == N/2) {
      // get scores
      int teamAScore = 0;
      int teamBScore = 0;

      for(int i = 0; i < N; i++) {
        if(teamA[i] == 1) {
          for(int j = 0; j < N; j++) {
            if(teamA[j] == 1 && j != i) {
              teamAScore += scores[i][j]; 
            } 
          }
        } else {
          for(int j = 0; j < N; j++) {
            if(teamA[j] == 0 && j != i) {
              teamBScore += scores[i][j]; 
            } 
          }
        }
      }
      
      teamAScore = teamAScore - teamBScore;

      return teamAScore > 0 ? teamAScore : -teamAScore;
    }

    int ret = Integer.MAX_VALUE;
    if(curIndex <= N - 1) {
      teamA[curIndex] = 1;
      ret = Math.min(solve(teamA, n + 1, curIndex + 1), ret);
      teamA[curIndex] = 0;
      ret = Math.min(solve(teamA, n, curIndex + 1), ret);
    }

    return ret;
  }
}