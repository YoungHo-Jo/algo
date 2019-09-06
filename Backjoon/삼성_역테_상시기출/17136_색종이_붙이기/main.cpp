#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>


using namespace std;

#define endl '\n'

bool board[10][10];
int maxBoard[10][10];
int leftPapers[6] = {
  0, 5, 5, 5, 5, 5
};

typedef pair<int, int> pii;
typedef pair<int, pii> pipii;

int check(int row, int col, int size) {
  if(size > 5) return size - 1;
  if(row >= 10 || col >= 10) return size - 1;
  if(board[row][col] == false) return size - 1;
  for(int d = 1; d < size; d++) {
    int i = row - d;
    int j = col - d;
    if(board[i][col] == false || board[row][j] == false) return size - 1;
  }

  return check(row + 1, col + 1, size + 1);
}

void remove(int row, int col, int size) {
  if(size <= 0) return;
  if(board[row][col] == false) return;
  
  remove(row + 1, col + 1, size - 1);
  remove(row + 1, col, size - 1);
  remove(row, col + 1, size - 1);
  board[row][col] = false;
}

int solve() { 
  priority_queue<pipii> pq;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      int size = check(i, j, 1);
      maxBoard[i][j] = size;
      if(size != 0) pq.push(pipii(size, pii(i, j)));
    }
  }

//  cout << "maxBoard: " << endl;
//  for(int i = 0; i < 10; i++) {
//    for(int j = 0; j < 10; j++) {
//      cout << maxBoard[i][j] << " ";
//    }
//    cout << endl;
//  }
//  cout << endl;

  

  int ret = 0;
  while(pq.empty() == false) {
    const pii& pos = pq.top().second;
    const int& maxSize = pq.top().first;
    
    if(leftPapers[maxSize] > 0) {
      // remove
      if(check(pos.first, pos.second, 1) == maxSize) {
        remove(pos.first, pos.second, maxSize);
        // cout << "remvoe: " << pos.first << " " << pos.second << " size: " << maxSize << endl;
        leftPapers[maxSize]--; 
        ret++;

//        cout << "After: " << endl;
//        for(int i = 0; i < 10; i++) {
//          for(int j = 0; j < 10; j++) {
//            cout << board[i][j] << " ";
//          }
//          cout << endl;
//        }
//        cout << endl;
        
      }

    } else {
     
    }

    pq.pop();
  }

  

  
  int remains = 0;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      if(board[i][j] == true) remains++;
    }
  }

  if(remains != 0) {
    if(remains <= leftPapers[1]) {
      ret += remains;
    } else {
      ret = -1;
    }
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  memset(board, false, sizeof(board));
  
  int inp;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      cin >> inp;
      board[i][j] = inp;
    }
  }

  cout << solve() << endl;


  return 0;
}
