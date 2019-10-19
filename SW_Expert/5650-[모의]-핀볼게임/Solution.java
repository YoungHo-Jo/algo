/*
  start: 2019.10.16 15:21
  end:
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

class Solution {
  static int N;
  static int[][] board;
  static int[][][] cache;

  static class Point {
    int row;
    int col;

    Point(int row, int col) {
      this.row = row;
      this.col = col;
    }

    @Override
    public boolean equals(Object obj) {
      if(obj instanceof Point) {
        Point point = (Point) obj;
        return point.row == this.row && point.col == this.col; 
      } 

      return false;
    }

    @Override
    public int hashCode() {
      return Objects.hash(this.row, this.col);
    }

    @Override
    public String toString() {
      return String.format("(%d, %d)", this.row, this.col);
    }
  }

  static class WormHole {
    Point p1;
    Point p2;

    WormHole(Point p) {
      this.p1 = p;
    }

    void setOther(Point p) {
      if(this.p2 == null) {
        this.p2 = p;
      } else {
        throw new RuntimeException();
      }
    }

    @Override
    public boolean equals(Object obj) {
      if(obj instanceof WormHole) {
        WormHole wormHole = (WormHole) obj;
        return wormHole.p1.equals(this.p1) && wormHole.p2.equals(this.p2);
      }

      return false;
    }

    @Override
    public int hashCode() {
      return Objects.hash(this.p1, this.p2);
    }

    @Override
    public String toString() {
      return this.p1.toString() + " " + this.p2.toString();
    }
  }
  
  static Map<Integer, WormHole> wormholes;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    
    int T = Integer.parseInt(br.readLine());

    board = new int[100][100];
    cache = new int[100][100][4];
    for(int i = 0; i < board.length; i++) {
      board[i] = new int[100];
      cache[i] = new int[100][4];

      for(int d = 0; d < 4; d++) {
        cache[i][d] = new int[4];
      }
    }

    for(int t = 1; t <= T; t++) {

      N = Integer.parseInt(br.readLine());
      
      wormholes = new HashMap<>();

      for(int i = 0; i < N; i++) {
        String[] line = br.readLine().split(" ");
        for(int j = 0; j < line.length; j++) {
          board[i][j] = Integer.parseInt(line[j]);
          Arrays.fill(cache[i][j], -1);
          
          if(board[i][j] >= 6) {
            int key = board[i][j];

            if(wormholes.containsKey(key)) {
              wormholes.get(key).setOther(new Point(i, j)); 
            } else {
              wormholes.put(key, new WormHole(new Point(i, j)));
            }
          }
        }
      }

      int ans = solve();
      System.out.println("#" + t + " " + ans);
    }

  }

  static int solve() {
    int ret = Integer.MIN_VALUE;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        if(board[i][j] != 0) continue;

        for(int d = 0; d < 4; d++) {
          // System.out.println("start: " + i + " " + j);
          ret = Math.max(ret, start(i, j, i, j, d, false));
        }
      }
    }
    
    return ret == Integer.MIN_VALUE ? 0 : ret;
  }

  static int[] dy = {
    -1, 0, 1, 0
  };
  static int[] dx = {
    0, 1, 0, -1
  };
  static int[][] dirWhenHit = {
    {0, 0, 0, 0},
    {2, 3, 1, 0}, 
    {1, 3, 0, 2},
    {3, 2, 0, 1},
    {2, 0, 3, 1},
    {2, 3, 0, 1}
  };

  static int start(int startRow, int startCol, int row, int col, int dir, boolean wasWormhole) {
    // System.out.println(row + " " + col +  " " + dir);
    if(row < 0 || row >= N || col < 0 || col >= N) {
      // wall
      dir = dirWhenHit[5][dir];
      int nextRow = row + dy[dir];
      int nextCol = col + dx[dir];
      
      if(nextRow == startRow && nextCol == startCol) {
        return 1;
      }
      
      return start(startRow, startCol, nextRow, nextCol, dir, false) + 1;
    } 

    int type = board[row][col];
    // System.out.println(type);
    if(type == -1) { // blackhole
      return 0;
    }

    // if(cache[row][col][dir] != -1) {
    //   return cache[row][col][dir];
    // }
    

    int nextDir = dir;
    if(type <= 5 && type != 0) {
      nextDir = dirWhenHit[type][dir];
    } else if(type >= 6 && wasWormhole == false) {
      WormHole wormHole = wormholes.get(type);

      Point p = new Point(row, col);
      Point nextP = wormHole.p1;
      if(nextP.equals(p)) {
        nextP = wormHole.p2;
      }

      return start(startRow, startCol, nextP.row, nextP.col, dir, true);
    }

    int nextRow = row + dy[nextDir];
    int nextCol = col + dx[nextDir];

    if(nextRow == startRow && nextCol == startCol) {
      return 0;
    }

    return start(startRow, startCol, nextRow, nextCol, nextDir, false) + (type <= 5 && type != 0 ? 1 : 0);  
  }
}