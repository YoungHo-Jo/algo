/*
  start: 2019.10.18 19:52
  end: 
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Deque;
import java.util.StringTokenizer;
import java.util.stream.Collectors;
import java.util.List;
import java.util.Scanner;
import java.util.ArrayDeque;

class Solution {
  
  static int[][] cover = new int[13][20];
  static int K, D, W;

  public static void main(String[] args) throws IOException {
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
     
    // int T = Integer.parseInt(br.readLine());
    Scanner sc = new Scanner(System.in);
    int T = sc.nextInt();

    for(int i = 0; i < cover.length; i++) {
      cover[i] = new int[20];
    }

    for(int t = 1; t <= T; t++) {
      // List<Integer> line = Arrays.stream(
      //   br.readLine().split(" ")  
      // ).map(str -> Integer.parseInt(str))
      // .collect(Collectors.toList());

      // D = line.get(0);
      // W = line.get(1);
      // K = line.get(2);

      // for(int i = 0; i < D; i++) {
      //   String[] row = br.readLine().split(" ");
      //   for(int j = 0; j < row.length; j++) {
      //     cover[i][j] = Integer.parseInt(row[j]);
      //   }
      // }
      D = sc.nextInt();
      W = sc.nextInt();
      K = sc.nextInt();

      for(int i = 0; i < D; i++) {
        for(int j = 0; j < W; j++) {
          cover[i][j] = sc.nextInt();
        }
      }

      int ans = solve();
      System.out.println("#" + t + " " + ans);
    }
  }

  static void print() {
    System.out.println("--print--");
    System.out.println(Arrays.stream(cover)
      .map(row -> Arrays.stream(row)
        .mapToObj(i -> String.valueOf(i))
        .collect(Collectors.joining(" "))
      )
      .collect(Collectors.joining("\n"))
    );
  }

  static int solve() {
    if(check(cover)) return 0;
    Deque<int[][]> deque = new ArrayDeque<>();
    Deque<Integer> cnt = new ArrayDeque<>();
    Deque<Integer> injectRows = new ArrayDeque<>();
    
    deque.addLast(cover);
    cnt.addLast(0);
    injectRows.addLast(-1);

    int ret = D;
    while(deque.isEmpty() == false) {
      int[][] front = deque.pollFirst();
      int frontCnt = cnt.pollFirst();

      if(frontCnt > D) return D;

      int rowToInject = injectRows.pollFirst() + 1;
      
      if(rowToInject >= D) {
        continue;  
      }

      if(ret < frontCnt) {
        continue;
      }

      int[][] copyForA = Arrays.stream(front)
        .map(int[]::clone)
        .toArray(int[][]::new);
      int[][] copyForB = Arrays.stream(front)
        .map(int[]::clone)
        .toArray(int[][]::new);
      
      inject(copyForA, rowToInject, 0);
      if(check(copyForA)) {
        ret = Math.min(ret, frontCnt + 1);
        continue;
      }

      inject(copyForB, rowToInject, 1);
      if(check(copyForB)) {
        ret = Math.min(ret, frontCnt + 1);
        continue;
      }
    
      deque.addLast(front);
      cnt.addLast(frontCnt);
      injectRows.addLast(rowToInject);

      deque.addLast(copyForA);
      cnt.add(frontCnt + 1);
      injectRows.addLast(rowToInject);

      deque.addLast(copyForB);
      cnt.add(frontCnt + 1);
      injectRows.addLast(rowToInject);
    }
    
    return ret;
  }

  static void inject(int[][] cover, int row, int type) {
    for(int j = 0; j < W; j++) {
      cover[row][j] = type;
    }
  }

  static boolean check(int[][] cover) {
    for(int j = 0; j < W; j++) {
      int prev = cover[0][j];

      int cntA = prev == 0 ? 1 : 0;
      int cntB = prev == 1 ? 1 : 0;
      
      int k = 0;
      for(int i = 1; i < D; i++) {
        int here = cover[i][j];
        if(prev != here) {
          cntA = here == 0 ? 1 : 0;
          cntB = here == 1 ? 1 : 0;
          prev = here;
        } else {
          cntA += here == 0 ? 1 : 0;
          cntB += here == 1 ? 1 : 0;
        }

        k = Math.max(k, cntA);
        k = Math.max(k, cntB);
      }

      if(k < K) {
        return false;
      }
    }

    return true;
  }
}