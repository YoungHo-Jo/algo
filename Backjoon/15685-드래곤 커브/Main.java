/*
  start: 2019.10.19 10:32
  end: 2019.10.19 13:12
*/

import java.util.ArrayList;
import java.util.Scanner;

class Main {

  static class Point {
    int x;
    int y;
    
    Point(int x, int y) {
      this.x = x;
      this.y = y;
    }
    
    @Override
    public boolean equals(Object obj) {
      if(obj instanceof Point) {
        Point p = (Point) obj; 
        return this.x == p.x && this.y == p.y;
      }

      return false;
    }

    @Override
    public String toString() {
      return String.format("(%d, %d)", this.x, this.y);
    }

    void rotate90(Point core) {
      int newX = -1*(this.y - core.y) + core.x;
      int newY = (this.x - core.x) + core.y;
    
      this.x = newX;
      this.y = newY;
    }
    
    Point(Point p) {
      this.x = p.x;
      this.y = p.y;
    } 
  }

  static int[][] board = new int[101][101];
  static int N;

  static int[] dy = {
    0, -1, 0, 1
  };
  static int[] dx = {
    1, 0, -1, 0
  };
  
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    N = sc.nextInt();

    for(int i = 0; i < board.length; i++) {
      board[i] = new int[101];
    }

    for(int i = 0; i < N; i++) {
      int x = sc.nextInt();
      int y = sc.nextInt();
      int d = sc.nextInt();
      int g = sc.nextInt();

      ArrayList<Point> curve = new ArrayList<>();
      curve.add(new Point(x, y));
      curve.add(new Point(x + dx[d], y + dy[d]));

      while(g > 0) {
        g--;

        Point core = curve.get(curve.size() - 1);
        ArrayList<Point> newPoints = new ArrayList<>();
        for(int p = curve.size() - 2; p >= 0; p--) {
          Point newP = new Point(curve.get(p));
          newP.rotate90(core);
          newPoints.add(newP);
        }

        curve.addAll(newPoints);
      }

      for(Point p: curve) {
        board[p.y][p.x] = 1;
      }
    }

    int ans = 0;
    for(int i = 0; i < board.length; i++) {
      for(int j = 0; j < board[i].length; j++) {
        if(check(board, i, j)) {
          ans++;
        }
      }
    }

    System.out.println(ans);
  }


  static int[] checkDx = {
    1, 1, 0
  };
  static int[] checkDy = {
    0, 1, 1
  };

  static boolean check(int[][] board, int row, int col) {
    if(board[row][col] == 0) return false;
    
    for(int d = 0; d < 3; d++) {
      int newRow = row + checkDy[d];
      int newCol = col + checkDx[d];

      if(newRow > 100 || newRow < 0 || newCol > 100 || newCol < 0) return false;

      if(board[newRow][newCol] == 0) return false;
    } 

    return true;
  }
}