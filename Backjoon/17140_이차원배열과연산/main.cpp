#include <iostream>
#include <queue>
#include <map>
#include <cstring>

using namespace std;

int r, c, k;

int board[101][101];

typedef pair<int, int> pii;

void simulate(int& h, int& w, bool growingWidth) {
  
  int newBoard[101][101];
  memset(newBoard, 0, sizeof(newBoard));
  int newSize = 0;
  
  int i = 0;
  int j = 0;

  priority_queue<pii> pq;
  for(growingWidth ? i = 0 : j = 0; growingWidth? i < h : j < w; growingWidth? i++ : j++) {

    map<int, int> count; 

    for(growingWidth ? j = 0 : i = 0; growingWidth ? j < w : i < h; growingWidth? j++ : i++) {
      const int& num = board[i][j];
      if(num == 0) {
        continue;
      }
      
      if(count.find(num) == count.end()) {
        count[num] = 0;
      }

      count[num]++;
    }

    for(auto it = count.begin(); it != count.end(); it++) {
      pq.push(pii(-it->second, -it->first));      
    }

    int row = 0;
    int col = 0;
    while(pq.empty() == false) {
      const pii& top = pq.top();
      
      if(growingWidth) {
        newBoard[i][col++] = -top.second;
        newBoard[i][col++] = -top.first; 

        newSize = max(newSize, col); 
      } else {
        newBoard[row++][j] = -top.second;
        newBoard[row++][j] = -top.first; 

        newSize = max(newSize, row);
      }

      pq.pop();
    }

  }

  if(growingWidth) {
    w = newSize;
  } else {
    h = newSize;
  }

  memcpy(board, newBoard, sizeof(newBoard));
}

int solve() {

  int t = 0;
  int w = 3;
  int h = 3;
  while(t <= 100) {
    if(board[r - 1][c - 1] == k) {
      break;
    }

    t++;
    
    if(w > h) {
      // grow height
      simulate(h, w, false);
    } else {
      // grow width 
      simulate(h, w, true);
    }

  }

  
  if(t > 100) {
    t = -1; 
  }
  return t;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> r >> c >> k;
  
  int inp;
  memset(board, 0, sizeof(board));
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      cin >> inp;
      board[i][j] = inp;
    }
  }

  cout << solve() << endl;

  
  

  return 0;

}
