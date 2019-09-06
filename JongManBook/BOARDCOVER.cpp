#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

#define endl '\n'
#ifdef DEBUG
#define D(x) cout << " [DEBUG] " << __FUNCTION__ << ":" << __LINE__ << " >> " << x
#else
#define D(x)
#endif


#define MAX 20
bool board[MAX][MAX];


const int coverDx[4][2] = {
  {1, 0}, // L
  {1, 1}, // ㄱ
  {1, 0}, 
  {0, -1}
};

const int coverDy[4][2] = {
  {1, 1},
  {0, 1},
  {0, 1}, 
  {1, 1}
};

bool isInRange(int y, int x, int ty, int tx) {
  return 0 <= ty && ty < y && 0 <= tx && tx < x;
}

int getCount(int h, int w) {
  
  int notFillX = -1, notFillY = -1;
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      if(board[y][x] == false) {
        notFillX = x;
        notFillY = y;
        break;
      }
    }
    if(notFillX != -1) break;
  }

  
  D("Found not fill point: " << notFillX << " " << notFillY << endl;)

  if(notFillX == -1) return 1;
  
  int ret = 0;
  for(int c = 0; c < 4; c++) {
    int px1 = coverDx[c][0] + notFillX;
    int py1 = coverDy[c][0] + notFillY;
    int px2 = coverDx[c][1] + notFillX;
    int py2 = coverDy[c][1] + notFillY;

    D("cover " << notFillY << " " << notFillX << " " << py1 << " " << px1 << " " << py2 << " " << px2 << endl;)

    if(isInRange(h, w, py1, px1) && 
      isInRange(h, w, py2, px2) &&
      board[py1][px1] == false &&
      board[py2][px2] == false) {
      
      D("Can cover " << endl);
      
      board[py1][px1] = board[py2][px2] = board[notFillY][notFillX] = true; 
      ret += getCount(h, w);
      board[py1][px1] = board[py2][px2] = board[notFillY][notFillX] = false; 
    } 
  }

  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  time_t start = clock();

  int testCase;
  cin >> testCase;
  for(int t = 0; t < testCase; t++) {
    int h, w;
    
    cin >> h >> w;
    char c;
    for(int y = 0; y < h; y++) {
      for(int x = 0; x < w; x++) {
        cin >> c;
        if(c == '#') board[y][x] = true;
        else board[y][x] = false;
      }
    }

    cout << getCount(h, w) << endl;
  }


  cout << "Total running time: " << clock() - start << endl;

  return 0;
}


