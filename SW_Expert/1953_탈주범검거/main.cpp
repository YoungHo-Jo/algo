#include <iostream>
#include <cstring>
#include <queue>


using namespace std;

#define endl '\n'

int board[50][50];
int N, M, R, C, L;
  
// up right down left is open?
const bool type[8][4] = {
  {0, 0, 0, 0}, // no use
  {1, 1, 1, 1}, // 1
  {1, 0, 1, 0}, // 2
  {0, 1, 0, 1}, // 3
  {1, 1, 0, 0}, // 4
  {0, 1, 1, 0}, // 5
  {0, 0, 1, 1}, // 6
  {1, 0, 0, 1} // 7
};

// up right down left
const int dy[4] = {
  -1, 0, 1, 0
};
const int dx[4] = {
  0, 1, 0, -1
};

// from ... to ... which direction have to check
const int toCheck[4] = {
  2, // go up, check down  
  3, // go right, check left
  0, // go down, check up
  1, // go left, check right 
}; // in type of the cell to go

typedef pair<int, int> pii;

int solve() {
  if(L == 1) return 1;
  
  queue<pii> bfs;
  queue<int> time;

  bfs.push(pii(R, C));
  time.push(0);
  
  bool discovered[50][50];
  memset(discovered, false, sizeof(discovered));

  int ret = -1;
  while(bfs.empty() == false) { 
    const pii& here = bfs.front();
    const int& t = time.front();
    const int& typeOfHere = board[here.first][here.second];
    if(t >= L) break; // timeout

    ret++;

    for(int d = 0; d < 4; d++) {
      int row = here.first + dy[d];
      int col = here.second + dx[d];

      if(row < 0 || col < 0 || row >= N || col >= M || discovered[row][col]) {
        continue;
      }

      int thereType = board[row][col];
      if(type[typeOfHere][d] && type[thereType][toCheck[d]]) {
        discovered[row][col] = true;
        bfs.push(pii(row, col));
        time.push(t + 1);
      }
    }

    bfs.pop();
    time.pop();
  }

  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  for(int tc = 1; tc <= T; tc++) {  
    // get input

    cin >> N >> M >> R >> C >> L;
    
    memset(board, 0, sizeof(board));
  
    int inp;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < M; j++) {
        cin >> inp;
        board[i][j] = inp; 
      }
    }

    cout << "#" << tc << " " << solve() << endl;
  }
  
  return 0;
}
