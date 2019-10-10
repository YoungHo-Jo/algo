/*
  start: 2019.10.10 15:44
  end: 2019.10.10 16:17
*/

import java.util.Scanner;
import java.util.Arrays;

class Solution {
  
  static int[][] board;
  static boolean[][] visited;
  static final int MAX = 8;

  static final int[] dx = {
    0, 1, 0, -1
  };

  static final int[] dy = {
    -1, 0, 1, 0
  };


  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    board = new int[MAX][MAX];
    visited = new boolean[MAX][MAX];
    for(int i = 0; i < MAX; i++) {
      board[i] = new int[MAX];
      visited[i] = new boolean[MAX];
      Arrays.fill(visited[i], false);
    }

    int T = sc.nextInt();
    for(int t = 1; t <= T; t++) {
      int N = sc.nextInt();
      int K = sc.nextInt();

      for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
          board[i][j] = sc.nextInt();
        }
      }

      int ans = solve(N, K);       

      System.out.println("#" + t + " " + ans);
    }
  }

  static int solve(int N, int K) {
    // find the highest
    int theHighest = Integer.MIN_VALUE;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        if(theHighest < board[i][j]) {
          theHighest = board[i][j];
        }
      }
    }

    int ret = 0;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        if(theHighest == board[i][j]) {
          visited[i][j] = true;
          ret = Math.max(ret, getLongest(N, K, i, j) + 1);
          visited[i][j] = false;
        }
      }
    } 

    return ret;
  }

  static int getLongest(int N, int K, int row, int col) {
    if(row >= N || row < 0 || col >= N || col < 0) {
      return 0;
    }

    // cachable
    int ret = 0;
    for(int d = 0; d < 4; d++) {
      int newRow = row + dy[d];
      int newCol = col + dx[d];
      
      int here = board[row][col];
      if(newRow >= N || newRow < 0 || newCol >= N || newCol < 0) {
        continue;
      }

      if(visited[newRow][newCol]) {
        continue;
      }

      int there = board[newRow][newCol];
      if(here > there) {
        visited[newRow][newCol] = true;
        printVisited(N);
        ret = Math.max(ret, getLongest(N, K, newRow, newCol) + 1);
        visited[newRow][newCol] = false;
      }

      if(here <= there && K != 0) {
        for(int k = 1; k <= K; k++) {
          if(there - k >= 0 && here > there - k) {
            visited[newRow][newCol] = true;
            board[newRow][newCol] -= k; 
            printVisited(N);
            ret = Math.max(ret, getLongest(N, 0, newRow, newCol) + 1);
            visited[newRow][newCol] = false;
            board[newRow][newCol] += k; 
          }
        }
      }
    }
    
    return ret;
  }

  static void printVisited(int N) {
    boolean print = false;

    if(print) {
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
          System.out.print(visited[i][j] ? "1 " : "0 "); 
        }
        System.out.println();
      }
      System.out.println();
    }
  }
}