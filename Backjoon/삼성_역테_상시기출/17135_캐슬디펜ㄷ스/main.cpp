#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

#define endl '\n'

int N, M, D;
bool board[16][15];
typedef pair<int, int> pii;

int dx[3] = { // left up right
  -1, 0, 1
};
int dy[3] = {
  0, -1, 0
};

int getDist(int y1, int x1, int y2, int x2) {
  return abs(y1 - y2) + abs(x1 - x2);
}

pii getClosed(int row, int col) {
  queue<pii> bfs;
  bfs.push(pii(row - 1, col)); // up
  bool visited[15][15];
  memset(visited, false, sizeof(visited));
  while(bfs.empty() == false) {
    const pii& here = bfs.front();
    if(board[here.first][here.second] == true) {
      return here;
    }

    visited[here.first][here.second] = true;
    
      
    for(int d = 0; d < 3; d++) {
      int i = here.first + dy[d];
      int j = here.second + dx[d];
      if(i < 0 || j < 0 || i >= N || j >= M) continue;
      if(getDist(row, col, i, j) <= D && visited[i][j] == false) {
        bfs.push(pii(i, j));
      }
    }

    bfs.pop();
  }
  
  return pii(-1, -1);
}

int solve() {
  // combination of archors

  int ret = 0;
  bool temp[16][15];
  for(int a = 0; a < M - 2; a++) {
    for(int b = a + 1; b < M - 1; b++) {
      for(int c = b + 1; c < M; c++) {
        memcpy(temp, board, sizeof(temp));
        
        // simulation
        bool done = false;
        int killNum = 0;
        queue<pii> q;
        while(done == false) {
          // kill enemy
          q.push(getClosed(N, a));
          q.push(getClosed(N, b));
          q.push(getClosed(N, c));

          while(q.empty() == false) {
            const pii& enemy = q.front();
            if(enemy.first != -1 && board[enemy.first][enemy.second] != false) {
              board[enemy.first][enemy.second] = false; // kill
              killNum++;
            }

            q.pop();
          }

          // go down 
          done = true;
          for(int i = N; i >= 0; i--) {
            for(int j = 0; j < M; j++) {
              if(i == N) {
                board[N - 1][j] = 0; // reach castle 
              } else if(i == 0) {
                board[0][j] = 0;
              } else {  
                board[i][j] = board[i - 1][j];
                if(board[i][j] == true) done = false;
              }
            }
          }

        }

        ret = max(ret, killNum);

        memcpy(board, temp, sizeof(board));
      }
    }
  }

  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  cin >> N >> M >> D;
  memset(board, false, sizeof(board));
  int inp;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      cin >> inp;
      board[i][j] = inp;
    }
  }

  cout << solve() << endl;



  
  return 0;
}
