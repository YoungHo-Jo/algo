#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef pair<int, int> pii;

int N, M;
int board[20][20];
pii shark;
int sharkSize = 2;
int eaten = 0;

int dy[4] = { // up left right down
  -1, 0, 0, 1 
};

int dx[4] = {
  0, -1, 1, 0
};

int solve() {
  int ret = 0;

  // find fish
  while(true) {
    queue<pii> bfs;
    queue<int> time;
    time.push(0);
    bfs.push(shark);
    bool discovered[20][20];
    memset(discovered, false, sizeof(discovered));

    pii toEat(-1, -1);      
    int eatTime = 0;
    while(bfs.empty() == false) {
      const pii& here = bfs.front();
      const int& t = time.front();
      
      if(board[here.first][here.second] < sharkSize && board[here.first][here.second] != 0) {
        if(toEat.first == -1) {
          toEat = here;
          eatTime = t;
        } else if(eatTime == t) { // bfs property
          toEat = toEat.first == here.first ? 
            (toEat.second < here.second ? toEat : here) : 
            (toEat.first < here.first ? toEat : here);
        } else if(t > eatTime) {  
          break; 
        }

      }
    
      // next 
      for(int d = 0; d < 4; d++) {
        int row = here.first + dy[d];
        int col = here.second + dx[d];

        // out of range or discovered
        if(row < 0 || col < 0 || row >= N || col >= N || discovered[row][col]) {
          continue;
        }

        // can't go if fish is bigger
        if(board[row][col] > sharkSize) {
          continue;
        }

        discovered[row][col] = true;
        bfs.push(pii(row, col));
        time.push(t + 1);
      }

      bfs.pop();
      time.pop();
    }
   
    if(toEat.first != -1) {
      // eat
      eaten++;
      board[toEat.first][toEat.second] = 0;

      // update shark position
      shark = toEat;
      
      // grow
      if(eaten == sharkSize) {
        eaten = 0;
        sharkSize++;
      }

      ret += eatTime;
    } else {
      // nothing to eat
      break;
    }
  }

  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  int inp;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cin >> inp;
      if(inp == 9) {
        shark = pii(i, j);
        board[i][j] = 0;
      } else {
        board[i][j] = inp;
      }
    }
  }

  cout << solve() << endl;

  return 0;
}
