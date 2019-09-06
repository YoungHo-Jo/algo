#include <iostream>
#include <list>
#include <cassert>
#include <utility>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <queue>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

#define MAX 700
#define endl '\n'
#define DEAD 0
#define LIVE 1
#define WAIT 2

char cell[MAX][MAX];
char state[MAX][MAX];
char times[MAX][MAX];

int N, M, K;

int count() {
  int ret = 0;
  for(int i = 0; i < MAX; i++) {
    for(int j = 0; j < MAX; j++) {
      if(state[i][j] != DEAD) {
        ret++;
      }
    }
  }

  return ret;
}

typedef struct _c {
  int i;
  int j;
  char t;
} Cell;

list<Cell> waits;
list<Cell> lives;
list<Cell> toCheck;

int solve() {
  while(K--) {

    // change state wait to live
    for(int i = 0; i < MAX; i++) {
      for(int j = 0; j < MAX; j++) {
        if(state[i][j] == DEAD) continue; // dead cell => pass

        char& leftTime = times[i][j];
        if(state[i][j] == WAIT) {
          if(leftTime == 0) {
            state[i][j] = LIVE;     
            leftTime = cell[i][j];
          } else {
            leftTime--;
          }
          
          assert(leftTime >= 0);
        }
      }
    }
    
    // grow
    for(int i = 0; i < MAX; i++) {
      for(int j = 0; j < MAX; j++) {
        if(cell[i][j] != 0) continue; // only empty cell
        
        char toGrow = 0;
        for(int d = 0; d < 4; d++) {
          int row = i + dy[d];  
          int col = j + dx[d];  
          if(row < 0 || row >= MAX || col < 0 || col >= MAX) continue; // out of range

          if(state[row][col] == LIVE) {
            toGrow = max(toGrow, cell[row][col]);
          }
        }

        if(toGrow != 0) {
          cell[i][j] = toGrow;
          state[i][j] = WAIT;
          times[i][j] = toGrow;
        }
      }
    }

    // chnage state, live to dead
  //  for(int i = 0; i < MAX; i++) {
  //    for(int j = 0; j < MAX; j++) {
  //      if(state[i][j] != LIVE) continue;

  //      char& leftTime = times[i][j];
  //      leftTime--;

  //      if(leftTime == 0) {
  //        state[i][j] = DEAD;
  //      }
  //    }
  //  }
  }

  return count();
}



int solve2() {
  while(K--) {
    // wait 0 to live
    for(list<Cell>::iterator it = waits.begin(); it != waits.end(); it++) {
      if(it->t == 0) {
        list<Cell>::iterator temp = it;
        temp--;
        
        Cell liveCell = *it;
        liveCell.t = cell[liveCell.i][liveCell.j];
        lives.push_back(liveCell); 

        // update state
        state[liveCell.i][liveCell.j] = LIVE;
        
        // update toCheck list
        for(int d = 0; d < 4; d++) {
          Cell cellToCheck = {liveCell.i + dy[d], liveCell.j + dx[d], 0};
          toCheck.push_back(cellToCheck);
        }
        
        // erase from wait list
        waits.erase(it); 
        it = temp;
      } else {
        it->t -= 1;
      }
    }
    
    // grow from toCheck list 
    for(list<Cell>::iterator it = toCheck.begin(); it != toCheck.end(); it++) {
      Cell c = *it;

      // already exists
      if(cell[c.i][c.j] != 0) {
        list<Cell>::iterator temp = it;
        temp--;
        toCheck.erase(it);
        it = temp;
        continue;
      }
      
      for(int d = 0; d < 4; d++) {
        int row = c.i + dy[d];
        int col = c.j + dx[d];
        
        if(row < 0 || row >= MAX || col < 0 || col >= MAX) continue; // out of range
        
        // from 4 ways
        if(state[row][col] == LIVE) { // only from LIVE cell
          c.t = max(c.t, cell[row][col]);
        }
      }

      if(c.t != 0) {
        waits.push_back(c);
        cell[c.i][c.j] = c.t;
        state[c.i][c.j] = WAIT;
      }
    }

    for(list<Cell>::iterator it = lives.begin(); it != lives.end(); it++) {
      if(it->t == 1) {
        list<Cell>::iterator temp = it;
        temp--;
          
        // update cell to dead
        state[it->i][it->j] = DEAD;
        
        lives.erase(it);
        it = temp;
      } else {
        it->t -= 1;
      }
    }

  }

  return waits.size() + lives.size();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int tc = 1; tc <= T; tc++) {
    cin >> N >> M >> K;
    
    memset(cell, 0, sizeof(cell));
    memset(state, 0, sizeof(state));
    //memset(times, 0, sizeof(times));
    
    waits = list<Cell>();
    toCheck = list<Cell>();
    lives = list<Cell>(); 


    int e;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < M; j++) {
        cin >> e;

        if(e == 0) continue;
        cell[i + 300][j + 300] = e;
        Cell c = {i + 300, j + 300, (char)e};
        waits.push_back(c);
        
        for(int d = 0; d < 4; d++) {
          Cell cellToCheck = {i + dy[d], j + dy[d], 0};
          toCheck.push_back(cellToCheck);
        }
        state[i + 300][j + 300] = WAIT;
      }
    }

    cout << "#" << tc << " " << solve2() << endl;
  }



  


  return 0;
}
