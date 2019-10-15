/*
  start: 2019.10.15 22:29
  end: 2019.10.16 00:41
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.ArrayDeque;
import java.util.HashMap;

class Solution {
  static int R;
  static int C;
  static int M;
  
  static class SharkProperty {
    int speed;
    int direction;
    int size;
    
    SharkProperty(int _speed, int _direction, int _size) {
      this.speed = _speed;
      this.direction = _direction;
      this.size = _size;
    }
  }

  static class Shark {
    int row;
    int col;
    int sharkNum;
    
    Shark(int _row, int _col, int sharkNum) {
      this.row = _row;
      this.col = _col;
      this.sharkNum = sharkNum;
    }
  }

  static Map<Integer, SharkProperty> sharks;
  static int[][] underSea; // shark number
  
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String[] firstLine = br.readLine().split(" ");
    
    R = Integer.parseInt(firstLine[0]);
    C = Integer.parseInt(firstLine[1]);
    M = Integer.parseInt(firstLine[2]);

    if(M == 0) {
      System.out.println("0");
      return;
    }

    sharks = new HashMap<>();
    underSea = new int[R][C];
    for(int i = 0; i < R; i++) {
      underSea[i] = new int[C];
    }
    
    for(int i = 0; i < M; i++) {
      String[] line = br.readLine().split(" ");
      int row = Integer.parseInt(line[0]) - 1;
      int col = Integer.parseInt(line[1]) - 1;
      int s = Integer.parseInt(line[2]);
      int d = Integer.parseInt(line[3]);
      int z = Integer.parseInt(line[4]);

      sharks.put(i + 1, new SharkProperty(s, d, z));
      underSea[row][col] = i + 1;
    }

    int fisherRow = 0;
    int fisherCol = -1;

    int ans = 0;

    while(fisherCol < C - 1) {
      // 1. move fisher
      fisherCol++;

      // 2. catch a shark
      int shark = -1;
      for(int i = 0; i < R; i++) {
        if(underSea[i][fisherCol] != 0) {
          shark = underSea[i][fisherCol];
          
          underSea[i][fisherCol] = 0;

          break;
        }
      }

      if(shark != -1) {
        ans += sharks.get(shark).size;
        sharks.remove(shark);
      }

      // 3. move sharks
      ArrayDeque<Shark> queue = new ArrayDeque<>();
      for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
          int sharkNum = underSea[i][j];

          if(sharkNum == 0) continue;

          Shark newShark = new Shark(i, j, sharkNum);
          next(newShark);

          queue.add(newShark);
          underSea[i][j] = 0;
        }
      }


      while(!queue.isEmpty()) {
        Shark s = queue.pollFirst();
        SharkProperty cur = sharks.get(s.sharkNum);

        if(underSea[s.row][s.col] != 0) {
          SharkProperty prev = sharks.get(underSea[s.row][s.col]);

          if(prev.size < cur.size) {
            sharks.remove(underSea[s.row][s.col]);
            underSea[s.row][s.col] = s.sharkNum;
          } else if(prev.size > cur.size) {
            sharks.remove(s.sharkNum);
          }
        } else {
          underSea[s.row][s.col] = s.sharkNum;
        }
      }
    }

    System.out.println(ans);
    
  }

  static void next(Shark shark) {
    SharkProperty property = sharks.get(shark.sharkNum);
    int leftSpeed = property.speed;
    int nextRow = shark.row;
    int nextCol = shark.col;
    int nextDirection = property.direction;

    while(leftSpeed > 0) {
      // System.out.println("before: ");
      // System.out.println(nextRow + " " + nextCol + " " + leftSpeed + " " + nextDirection);
      if(nextDirection == 1) { // up
        if(calc(nextRow, leftSpeed, nextDirection) < 0) {
          leftSpeed -= nextRow;
          nextRow = 0;
          nextDirection = 2;
        } else {
          nextRow = calc(nextRow, leftSpeed, nextDirection);
          break;
        }
      } else if(nextDirection == 2) {
        if(calc(nextRow, leftSpeed, nextDirection) >= R) {
          leftSpeed -= (R - nextRow - 1);
          nextRow = R - 1;
          nextDirection = 1;
        } else {
          nextRow = calc(nextRow, leftSpeed, nextDirection);
          break;
        }
      } else  if(nextDirection == 3) { // right
        if(calc(nextCol, leftSpeed, nextDirection) >= C) {
          leftSpeed -= (C - nextCol - 1);
          nextCol = C - 1;
          nextDirection = 4;
        } else {
          nextCol = calc(nextCol, leftSpeed, nextDirection);
          break;
        }
      } else if(nextDirection == 4) { // left
        if(calc(nextCol, leftSpeed, nextDirection) < 0) {
          leftSpeed -= nextCol;
          nextCol = 0;
          nextDirection = 3;
        } else {
          nextCol = calc(nextCol, leftSpeed, nextDirection);
          break;
        }
      }
      // System.out.println("after: "); System.out.println(nextRow + " " + nextCol + " " + leftSpeed + " " + nextDirection);
    }

    // System.out.println("final: ");
    // System.out.println(shark.sharkNum + " " + nextRow + " " + nextCol + " " + nextDirection);

    shark.row = nextRow;
    shark.col = nextCol;
    property.direction = nextDirection;
  }

  static int calc(int cur, int speed, int d) {
    if(d == 1 || d == 4) {
      return cur - speed;
    } else {
      return cur + speed;
    }
  }

  static void print(int[][] arr) {
    for(int i = 0; i < arr.length; i++) {
      for(int j = 0; j < arr[i].length; j++) {
        System.out.print(arr[i][j] + " ");
      }  
      System.out.println();
    }
  }
}
