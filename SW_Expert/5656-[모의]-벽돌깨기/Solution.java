import java.util.Scanner;

class Solution {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int T = Integer.parseInt(sc.nextLine());

    for(int t = 1; t <= T; t++) {
      String nwh = sc.nextLine();
      String[] nwhTokens = nwh.split(" ");
      
      int n = Integer.parseInt(nwhTokens[0]);
      int w = Integer.parseInt(nwhTokens[1]);
      int h = Integer.parseInt(nwhTokens[2]);

      int[][] board = new int[h][w];
      for(int i = 0; i < w; i++) {
        board[i] = new int[w];
      }

      for(int i = 0; i < h; i++) {
        String line = sc.nextLine();
        String[] tokens = line.split(" ");
        for(int j = 0; j < tokens.length; j++) {
          board[i][j] = Integer.parseInt(tokens[j]);
        }
      }

      int ans = getMax(board, n);

      System.out.println("#" + t + " " + ans);
    }
  }

  static void printBoard(int[][] board) {
    System.out.println("Print board: ");
    for(int i = 0; i < board.length; i++) {
      for(int j = 0; j < board[i].length; j++) {
        System.out.print(board[i][j] + " ");
      }
      System.out.println();
    }
  }

  static int getMax(int[][] board, int n) {
    return getMax(board, n, 0);
  }

  static int getMax(int[][] board, int n, int cur) {
    if(cur == n) {
      return count(board);
    } 


    int ret = Integer.MAX_VALUE;
    for(int j = 0; j < board[0].length; j++) {
      int[][] copied = copy(board);
      boolean nothingToDestropy = destroy(copied, j);
      if(nothingToDestropy == false) {
        shrink(copied);
        
        ret = Math.min(ret, getMax(copied, n, cur + 1));
      } else {
        if(checkAll0s(board)) {
          ret = 0;
          break;
        }
      }
    }

    return ret;
  }

  static int[][] copy(int[][] board) {
    int h = board.length;
    int w = board[0].length;

    int[][] copiedBoard = new int[h][w];
    for(int i = 0; i < h; i++) {
      copiedBoard[i] = new int[w];
      for(int j = 0; j < w; j++) {
        copiedBoard[i][j] = board[i][j];        
      }
    }

    return copiedBoard;
  }

  static boolean destroy(int[][] board, int x) {
    int top = findTop(board, x);
    if(top == -1) {
      return true;
    }

    destroy(board, top, x);
    return false;
  }

  static void destroy(int[][] board, int y, int x) {
    int h = board.length;
    int w = board[0].length;
    if(y >= h || y < 0 || x >= w || x < 0) return;

    int n = board[y][x];
    if(n == 0) return;
    if(n == 1) {
      board[y][x] = 0;
      return;
    }

    board[y][x] = 0;
    // up
    for(int i = y - 1; i >= 0; i--) {
      if(y - i >= n) break;
      destroy(board, i, x);
    }

    // right 
    for(int j = x + 1; j < w; j++) {
      if(j - x >= n) break;
      destroy(board, y, j);
    }

    // down
    for(int i = y + 1; i < h; i++) {
      if(i - y >= n) break;
      destroy(board, i, x);
    }

    // left
    for(int j = x - 1; j >= 0; j--) {
      if(x - j >= n) break;
      destroy(board, y, j);
    }
  }

  static int findTop(int[][] board, int x) {
    for(int i = 0; i < board.length; i++) {
      if(board[i][x] != 0) {
        return i;
      }  
    }

    return -1;
  }

  static void shrink(int[][] board) {
    int h = board.length;
    int w = board[0].length;
    
    for(int j = 0; j < w; j++) {
      int zeroPointer = h - 1;

      for(int i = h - 1; i >= 0; i--) {
        if(board[i][j] > 0) {
          while(board[zeroPointer][j] != 0 && zeroPointer > i) {
            zeroPointer--;
          }

          if(board[zeroPointer][j] == 0) {
            board[zeroPointer][j] = board[i][j];
            board[i][j] = 0;
          }
        } 
      }
    }    

  }


  static int count(int[][] board) {
    int cnt = 0;
    for(int i = 0; i < board.length; i++) {
      for(int j = 0; j < board[i].length; j++) {
        if(board[i][j] != 0) {
          cnt++;
        }
      }
    }

    return cnt;
  }

  static boolean checkAll0s(int[][] board) {
    for(int i = 0; i < board.length; i++) {
      for(int j = 0; j < board[i].length; j++) {
        if(board[i][j] > 0) {
          return false;
        }
      }  
    }

    return true;
  }
  
}