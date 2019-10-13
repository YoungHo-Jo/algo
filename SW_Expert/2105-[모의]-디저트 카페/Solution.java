/*
  start: 2019.10.13 20:29
  end: 2019.10.13 21:39
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

class Solution {

  static final int MAX = 20;
  static int[][] map = new int[20][20];
  static boolean[] ateDesert = new boolean[101];
  static int N;

  // up left, up right, down right, down left
  static int[] dy = {
    -1, -1, 1, 1
  };
  static int[] dx = {
    -1, 1, 1, -1
  };

  static int[] nextDirection = {
    -1, 0, 1, 2, 
  };


  public static void main(String[] args) throws IOException {
    Scanner sc = new Scanner(System.in);

    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    
    int T = Integer.parseInt(reader.readLine());
    for(int t = 1; t <= T; t++) {
      N = Integer.parseInt(reader.readLine());

      

      for(int i = 0; i < N; i++) {
        String line = reader.readLine();
        String[] tokens = line.split(" ");
        for(int j = 0; j < N; j++) {
          map[i][j] = Integer.parseInt(tokens[j]);
        }
      }

      int ans = solve();

      System.out.println("#" + t + " " + ans);
    }
  }

  static int solve() {

    int ret = -1;

    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        ret = Math.max(ret, visit(i, j, i, j, 3));
      }
    }

    return ret;
  }

  static int visit(int startRow, int startCol, int curRow, int curCol, int dir) {
    if(startRow == curRow && startCol == curCol && dir == 0) {
      return count();
    }

    if(startRow > curRow) {
      return -1;
    }

    // straight
    int straightRow = dy[dir] + curRow;
    int straightCol = dx[dir] + curCol;

    int ret = -1;
    if(!(straightCol >= N || straightCol < 0 || straightRow >= N || straightRow < 0)) {
      int desertToEat = map[straightRow][straightCol];
      
      if(!ateDesert[desertToEat]) {
        ateDesert[desertToEat] = true;
        ret = visit(startRow, startCol, straightRow, straightCol, dir);
        ateDesert[desertToEat] = false;
      }
    } 

    // turn
    int dirToTurn = nextDirection[dir];
    if(dirToTurn != -1) {
      int turnRow = dy[dirToTurn] + curRow;
      int turnCol = dx[dirToTurn] + curCol;
      
      if(!(turnRow >= N || turnRow < 0 || turnCol >= N || turnCol < 0)) {
        int desertToEat = map[turnRow][turnCol];
        
        if(!ateDesert[desertToEat]) {
          ateDesert[desertToEat] = true;
          ret = Math.max(ret, visit(startRow, startCol, turnRow, turnCol, dirToTurn));
          ateDesert[desertToEat] = false;
        }
      }
    }

    return ret;
  }

  static int count() {
    int ret = 0;
    for(int i = 0; i < ateDesert.length; i++) {
      if(ateDesert[i]) ret++;
    }

    return ret;
  }

  static void print() {
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {

        System.out.print(map[i][j] + " ");
      }
      System.out.println();
    }
  }

  
}