/*
  start: 2019.10.11 12:46
  end: 2019.10.11 13:15
*/

import java.nio.channels.NetworkChannel;
import java.util.Arrays;
import java.util.Scanner;



class Solution {
  
  static int[][] map = new int[50][50];
  static int N, M, R, C, L;
  static int[][] visited;
  
  static final int[][] types = {
    { 
      0, 0, 0, 0
    }, // up right down left
    {
      1, 1, 1, 1
    },
    {
      1, 0, 1, 0
    },
    {
      0, 1, 0, 1
    },
    {
      1, 1, 0, 0
    },
    {
      0, 1, 1, 0
    },
    {
      0, 0, 1, 1
    },
    {
      1, 0, 0, 1
    }
  };

  static final int[] dx = {
    0, 1, 0, -1
  };
  static final int[] dy = {
    -1, 0, 1, 0
  };

  
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int T = sc.nextInt();

    for(int t = 1; t <= T; t++) {
      N = sc.nextInt();
      M = sc.nextInt();
      R = sc.nextInt();
      C = sc.nextInt();
      L = sc.nextInt();
  
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          map[i][j] = sc.nextInt();
        }
      }

      visited = new int[N][M];
      for(int i = 0; i < visited.length; i++) {
        visited[i] = new int[M];
        Arrays.fill(visited[i], -1);
      }

      visit(R, C, L);
      int ans = 0;
      for(int i = 0; i < visited.length; i++) {
        for(int j = 0; j < visited[i].length; j++) {
          if(visited[i][j] != -1) {
            ans++;
          }
        }
      }


      System.out.println("#" + t + " " + ans);
    }
  }

  static void visit(int row, int col, int l) {
    if(l == 0) return;
    int type = map[row][col];

    if(type == 0) return;

    visited[row][col] = l;

    int[] here = types[type];
    
    for(int d = 0; d < 4; d++) {
      int nextRow = dy[d] + row;
      int nextCol = dx[d] + col;

      if(nextRow < 0 || nextRow >= N || nextCol < 0 || nextCol >= M) {
        continue;
      }

      if(visited[nextRow][nextCol] > l) {
        continue;
      }
      
      if(here[d] == 1) {
        int nextType = map[nextRow][nextCol];
        int[] next = types[nextType];
        
        if((d == 0 && next[2] == 1)
          || (d == 1 && next[3] == 1)
          || (d == 2 && next[0] == 1)
          || (d == 3 && next[1] == 1)) {
            visit(nextRow, nextCol, l - 1);
        }
      }       
    }
  }
}