/*
  start: 2019.10.16 10:56
  end: 2019.10.16 12:38
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.ArrayDeque;
import java.util.Map;
import java.util.TreeMap;
import java.util.Arrays;

class Solution {

  static int N;
  static final int OFFSET = 2000;
  static final int MAX = 4002;

  static int[][] board;
  static Map<Integer, Atom> atoms;

  static class Atom {
    int x;
    int y;
    int dir;
    int e;
    
    Atom(int _x, int _y, int _dir, int _e) {
      this.x = _x;
      this.y = _y;
      this.dir = _dir;
      this.e = _e;
    }
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    int T = Integer.parseInt(br.readLine());
    
    board = new int[MAX][MAX];
    for(int i = 0; i < MAX; i++) {
      board[i] = new int[MAX];
    }

    for(int t = 1; t <= T; t++) {
      N = Integer.parseInt(br.readLine());

      atoms = new TreeMap<>();
      for(int i = 0; i < MAX; i++) {
        Arrays.fill(board[i], 0);
      }
      
      for(int i = 0; i < N; i++) {
        String[] line = br.readLine().split(" ");

        int x = Integer.parseInt(line[0])*2 + OFFSET;
        int y = Integer.parseInt(line[1])*2 + OFFSET;
        int d = Integer.parseInt(line[2]);
        int e = Integer.parseInt(line[3]);

        int key = i + 1;

        atoms.put(key, new Atom(x, y, d, e));
        board[y][x] = key;
      }

      int ans = 0;
      int time = 0;
      while(atoms.isEmpty() == false) {
        time++;
        int temp = solve();
        ans += temp;
      }

      System.out.println("#" + t + " " + ans);
    }

  }

  static int[] dy = {
    1, -1, 0, 0
  };
  static int[] dx = {
    0, 0, -1, 1
  };


  static int solve() {

    int ret = 0;

    for(Map.Entry<Integer, Atom> entry: atoms.entrySet()) {
      Atom atom = entry.getValue();

      board[atom.y][atom.x] = 0;

      int newX = atom.x + dx[atom.dir];
      int newY = atom.y + dy[atom.dir];

      atom.x = newX;
      atom.y = newY;
    }

    ArrayDeque<Integer> collisions = new ArrayDeque<>();
    ArrayDeque<Integer> outs = new ArrayDeque<>();


    for(Map.Entry<Integer, Atom> entry: atoms.entrySet()) {
      Atom atom = entry.getValue();

      int originX = atom.x - dx[atom.dir];
      int originY = atom.y - dy[atom.dir];

      if(atom.y >= MAX || atom.y < 0 || atom.x >= MAX || atom.x < 0) {
        // System.out.println(atom.y + " " + atom.x);
        outs.add(entry.getKey());
        continue;
      }

      if(board[atom.y][atom.x] != 0 || board[originY][originX] != 0) {
        // int atomNumInOrigin = board[originY][originX];
        // Atom atomInOrigin = atoms.get(atomNumInOrigin);

        // if(atomInOrigin != null) {
        //   if((!(atom.dir == 0 && atomInOrigin.dir == 1)
        //       || (atom.dir == 1 && atomInOrigin.dir == 0)
        //       || (atom.dir == 2 && atomInOrigin.dir == 3) 
        //       || (atom.dir == 3 && atomInOrigin.dir == 4))) {
        //         continue;
        //       }
        // }

        // System.out.println("coliision?: " + entry.getKey() + " -  " + board[atom.y][atom.x] + " " + board[originY][originX]);
        // System.out.println(originY + " " + originX);
        // collision
        collisions.add(entry.getKey());
        collisions.add(board[atom.y][atom.x]);
        // if(atomInOrigin != null) {
        //   collisions.add(atomNumInOrigin);
        // }
      } else {
        board[atom.y][atom.x] = entry.getKey();
      }
    }

    while(collisions.isEmpty() == false) {
      int atomNum = collisions.poll();

      Atom atom = atoms.get(atomNum);
      if(atom != null) {
        // System.out.println("coliision: " + atom.y + " " + atom.x + " " + atom.e);
        board[atom.y][atom.x] = 0;
        ret += atom.e;
        atoms.remove(atomNum);
      }
    }
    
    while(outs.isEmpty() == false) {
      int atomNum = outs.poll();
      if(atoms.containsKey(atomNum)) {
        // System.out.println("out: " + atoms.get(atomNum).e);
        atoms.remove(atomNum);
      }
    }


    return ret;
  }

}