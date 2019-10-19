/*
  start: 2019.10.19 18:44
  end: 2019.10.19 19:46
*/

import java.util.Arrays;
import java.util.Scanner;
import java.util.function.BinaryOperator;
import java.util.stream.Collectors;

class Main {

  static int[][] map;
  static int R, C, T;

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    
    R = sc.nextInt();
    C = sc.nextInt();
    T = sc.nextInt();

    map = new int[R][C];
  

    int head = -1;
    int tail = -1;

    for(int i = 0; i < map.length; i++) {
      map[i] = new int[C];

      for(int j = 0; j < map[i].length; j++) {
        map[i][j] = sc.nextInt();

        if(map[i][j] == -1) {
          if(head == -1) {
            head = i;
          } else {
            tail = i;
          }
        }
      }
    }

    int[][] temp = new int[R][C];
    Arrays.stream(temp)
      .forEach(row -> row = new int[C]);

    while(T > 0) {
      T--;

      // spread
      for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
          int here = map[i][j];

          if(here == -1 || here == 0) {
            continue;
          }

          int cnt = 0;
          for(int d = 0; d < 4; d++) {
            int newRow = i + dy[d];
            int newCol = j + dx[d];
            
            if(newRow >= R || newRow < 0 || newCol >= C || newCol < 0) {
              continue;
            }

            if(newCol == 0 && (newRow == head || newRow == tail)) {
              continue;
            }

            temp[newRow][newCol] += here/5;
            cnt++;  
          }

          temp[i][j] += here - cnt*(here/5);
        }
      }

      // air circular
      counterClockwise(temp, head);
      clockwise(temp, tail);

      for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
          map[i][j] = temp[i][j];
          temp[i][j] = 0;
        }
      }
      
    } 

    int ans = 0;
    for(int i = 0; i < map.length; i++) {
      for(int j = 0; j < map[i].length; j++) {
        if(map[i][j] > 0) {
          ans += map[i][j];
        }
      }
    }

    System.out.println(ans);
  }

  static void counterClockwise(int[][] temp, int head) {
    int end = temp[head][C - 1];
    for(int j = C - 1; j >= 2; j--) {
      temp[head][j] = temp[head][j - 1];
    } 
    temp[head][1] = 0;

    int top = temp[0][C - 1];
    for(int i = 0; i <= head - 2; i++) {
      temp[i][C - 1] = temp[i + 1][C - 1];
    }
    temp[head - 1][C - 1] = end;

    int left = temp[0][0];
    for(int j = 0; j < C - 2; j++) {
      temp[0][j] = temp[0][j + 1];
    }
    temp[0][C - 2] = top;

    for(int i = head - 1; i > 0; i--) {
      temp[i][0] = temp[i - 1][0];
    }
    temp[1][0] = left;
  }

  static void clockwise(int[][] temp, int tail) {
    for(int i = tail + 1; i < R - 1; i++) {
      swap(temp, i, 0, i + 1, 0);
    }

    for(int j = 0; j < C - 1; j++) {
      swap(temp, R - 1, j, R - 1, j + 1);
    }

    for(int i = R - 1; i > tail; i--) {
      swap(temp, i, C - 1, i - 1, C - 1);
    }

    for(int j = C - 1; j > 1; j--) {
      swap(temp, tail, j, tail, j - 1);
    }
    
    temp[tail][1] = 0;
  }

  static void swap(int[][] temp, int lhsRow, int lhsCol, int rhsRow, int rhsCol) {
    int tmp = temp[lhsRow][lhsCol];
    temp[lhsRow][lhsCol] = temp[rhsRow][rhsCol];
    temp[rhsRow][rhsCol] = tmp;
  }

  static void print(int[][] temp) {
    System.out.println("--print--");
    System.out.println(
      Arrays.stream(temp)
        .map(row -> Arrays.stream(row)
          .mapToObj(i -> String.valueOf(i))
          .collect(Collectors.joining(" "))
        )
        .collect(Collectors.joining("\n"))
    );
  }

  static final int[] dy = {
    -1, 0, 1, 0
  };
  static final int[] dx = {
    0, 1, 0, -1
  };
}