import java.util.ArrayList;
import java.util.Arrays;
import java.lang.StringBuilder;

class Solution {
  public int solution(int m, int n, String[] board) {
    int answer = 0;

    final int[] dRow = new int[] {
      0, 1, 1,
    };

    final int[] dCol = new int[] {
      1, 0, 1
    };

    char[][] charBoard = Arrays.stream(board)
      .map(s -> s.toCharArray())
      .toArray(size -> new char[size][]);

    while(true) {
      int temp = answer;

      // find the blocks to remove
      ArrayList<Integer> rowToRemove = new ArrayList<>();
      ArrayList<Integer> colToRemove = new ArrayList<>();
      for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {

          boolean found = true;
          int[] rows = new int[3];
          int[] cols = new int[3];
          for(int d = 0; d < 3; d++) {
            int row = dRow[d] + i;
            int col = dCol[d] + j;
            
            if(row >= m || col >= n || charBoard[row][col] != charBoard[i][j]) {
              found = false;
              break;
            }


            rows[d] = row;
            cols[d] = col;
          }

          if(found == false) continue;
          
          Arrays.stream(rows).forEach(r -> rowToRemove.add(r));
          Arrays.stream(cols).forEach(c -> colToRemove.add(c));
          rowToRemove.add(i);
          colToRemove.add(j);
        }
      }
    
      for(int i = 0; i < rowToRemove.size(); i++) {
        int row = rowToRemove.get(i);
        int col = colToRemove.get(i);
        if(charBoard[row][col] != 'X') {
          charBoard[row][col] = 'X';
          answer++;
        }
      }

      for(int j = 0; j < n; j++) {
        int blankRow = m - 1;
        for(int i = m - 1; i >= 0; i--) {
          if(charBoard[i][j] != 'X' && charBoard[blankRow][j] == 'X') {
            charBoard[blankRow][j] = charBoard[i][j];
            charBoard[i][j] = 'X';
            blankRow--;
          } else if(charBoard[blankRow][j] != 'X') {
            blankRow--;
          }
        }
      } 
      
      if(temp == answer) {
        break;
      }

    }    

    return answer;
  }
}