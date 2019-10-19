/*
  start: 2019.10.19 19:48
  end: 
*/

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Collectors;

class Main {

  static int N, LHS, RHS;
  static int[][] map;

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    
    N = sc.nextInt();
    LHS = sc.nextInt();
    RHS = sc.nextInt();

    map = new int[N][N];
    Arrays.stream(map)
      .forEach(row -> row = new int[N]);

    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        map[i][j] = sc.nextInt();
      }
    }

    int[][] isOpen = new int[N][N];
    for(int i = 0; i < isOpen.length; i++) {
      isOpen[i] = new int[N];
    }

    int ans = 0;
    while(true) {
      int lastNumbering = 0;
      boolean once = false;
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

          if(isOpen[i][j] > 0) continue;

          // int here = map[i][j];

          // for(int d = 0; d < 4; d++) {
          //   int row = i + dy[d];
          //   int col = j + dx[d];

          //   if(row < 0 || row >= N || col < 0 || col >= N) {
          //     continue;
          //   }

          //   int there = map[row][col];

          //   int diff = Math.abs(here - there);
          //   if(L <= diff && diff <= R) {

          //     if(isOpen[i][j] != 0) {
          //       isOpen[row][col] = isOpen[i][j];
          //     } else if(isOpen[row][col] != 0) {
          //       isOpen[i][j] = isOpen[row][col];
          //     } else if(isOpen[row][col] == 0 && isOpen[i][j] == 0) {
          //       isOpen[i][j] = ++lastNumbering;
          //       isOpen[row][col] = lastNumbering;
          //     } else {
          //       int minNumber = Math.min(isOpen[i][j], isOpen[row][col]);
          //       isOpen[i][j] = isOpen[row][col] = minNumber;
          //     }
          //   }
          // }

          ArrayDeque<Integer> rowStack = new ArrayDeque<>();
          ArrayDeque<Integer> colStack = new ArrayDeque<>();
          rowStack.addLast(i);
          colStack.addLast(i);

          lastNumbering++;
          while(rowStack.isEmpty() == false) {
            int row = rowStack.pollFirst();
            int col = colStack.pollFirst();

            int here = map[row][col];

            for(int d = 0; d < 4; d++) {
              int newRow = row + dy[d];
              int newCol = col + dx[d];

              if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N) {
                continue;
              }

              if(isOpen[newRow][newCol] > 0) continue;

              int diff = Math.abs(here - map[newRow][newCol]);
              if(LHS <= diff && diff <= RHS) {
                isOpen[row][col] = lastNumbering;
                isOpen[newRow][newCol] = lastNumbering;
                
                rowStack.addLast(newRow);
                colStack.addLast(newCol);

                once = once || true;
              }
            }
          }
        }
      }

      // print(isOpen);

      if(once == false) {
        break;
      }

      ans++;
      
      int[] sumByNumbering = new int[lastNumbering + 1];
      int[] cntByNumbering = new int[lastNumbering + 1];

      for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
          int number = isOpen[i][j];

          if(number != 0) {
            cntByNumbering[number]++;
            sumByNumbering[number] += map[i][j];
          }
        }
      }

      for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
          int number = isOpen[i][j];
          if(number != 0) {
            map[i][j] = sumByNumbering[number] / cntByNumbering[number];
          }

          // init
          isOpen[i][j] = 0;
        }
      }
    }

    System.out.println(ans);
    
  }

  static void print(int[][] arr) {
    System.out.println("--print--");
    System.out.println(
      Arrays.stream(arr)
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
