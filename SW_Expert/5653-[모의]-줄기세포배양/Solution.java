import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/*
  start: 2019.10.05 19:40
  end: 

  https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo
*/

class Solution {

  static class Cell {
    int x;
    int left;
    boolean isPropagated;

    Cell(int _x) {
      this.x = _x;
      this.left = this.x;
      this.isPropagated = false;
    }
  }

  static int[] dy = {
    -1, 0, 1, 0
  };
  static int[] dx = {
    0, 1, 0, -1
  };


  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int T = Integer.parseInt(sc.nextLine());
    
    for(int t = 1; t <= T; t++) {
      String[] nmk = sc.nextLine().split(" ");
      int n = Integer.parseInt(nmk[0]);
      int m = Integer.parseInt(nmk[1]);
      int k = Integer.parseInt(nmk[2]);

      Map<Integer, Map<Integer, Cell>> newCells = new TreeMap<>();
      Map<Integer, Map<Integer, Cell>> deactive = new TreeMap<>();
      Map<Integer, Set<Integer>> dead = new TreeMap<>();

      for(int i = 0; i < n; i++) {
        String[] tokens = sc.nextLine().split(" ");
        for(int j = 0; j < tokens.length; j++) {
          if(tokens[j].equals("0")) {
            continue;
          }

          int x = Integer.parseInt(tokens[j]);

          deactive.putIfAbsent(i, new TreeMap<>());
          deactive.get(i).put(j, new Cell(x));
        }
      }

      while(k > 0) {
        k--;

        // deactive to active
        for(Integer row: deactive.keySet()) {
          
          ArrayList<Integer> colToDead = new ArrayList<>();
          
          for(Integer col: deactive.get(row).keySet()) {
            Cell c = deactive.get(row).get(col);
            c.left = c.left - 1;

            if(c.left < 0 && !c.isPropagated) {
              // active
              c.isPropagated = true;
              c.left = c.x - 1;

              for(int d = 0; d < 4; d++) {
                int newRow = row + dy[d];
                int newCol = col + dx[d];

                newCells.putIfAbsent(newRow, new TreeMap<>());
                if(newCells.get(newRow).containsKey(newCol)) {
                  Cell prev = newCells.get(newRow).get(newCol);

                  if(prev.x > c.x) {
                    continue;
                  }
                }

                newCells.get(newRow).put(newCol, new Cell(c.x));
              }
            }

            if(c.left == 0 && c.isPropagated) {
              // dead
              colToDead.add(col);

              dead.putIfAbsent(row, new TreeSet<>());
              dead.get(row).add(col); // set dead
            } 
          }

          for(Integer col: colToDead) {
            deactive.get(row).remove(col);
          }
        }

        for(Integer row: newCells.keySet()) {
          for(Integer col: newCells.get(row).keySet()) {
            boolean alreadyInCell = deactive.containsKey(row) ? deactive.get(row).containsKey(col) : false;
            alreadyInCell = alreadyInCell || (dead.containsKey(row) ? dead.get(row).contains(col) : false);
            
            if(!alreadyInCell) {
              Cell c = newCells.get(row).get(col);

              deactive.putIfAbsent(row, new TreeMap<>());
              deactive.get(row).put(col, c);
            }
          }
        }

        // print(deactive); System.out.println(count(deactive));
      }

      System.out.println("#" + t + " " + count(deactive));
    }


  }

  static void print(Map<Integer, Map<Integer, Cell>> table) {
    for(Integer row: table.keySet()) {
      for(Integer col: table.get(row).keySet()) {
        System.out.println(String.format("(%d, %d): %d", row, col, table.get(row).get(col).left));
      }
    }
  }

  static int count(Map<Integer, Map<Integer, Cell>> table) {
    int cnt = 0;
    for(Integer row: table.keySet()) {
      cnt += table.get(row).keySet().size();
    }

    return cnt;
  }
}



