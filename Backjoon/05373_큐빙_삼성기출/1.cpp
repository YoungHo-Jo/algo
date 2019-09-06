#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define endl '\n'

int n;
#define CLK 0
#define CCLK 1

#define U 0
#define D 1
#define F 2
#define B 3
#define L 4
#define R 5

char faces[6][3][3];
const char initalFaces[6] = {'w', 'y', 'r', 'o', 'g', 'b'};

const int effectFaces[6][4] = {
  {3, 5, 2, 4}, // up
  {2, 5, 3, 4}, // down
  {0, 5, 1, 4}, // front
  {0, 5, 1, 4}, // back
  {0, 2, 1, 3}, // left
  {0, 3, 1, 2}, // right
};

typedef pair<int, int> pii;

const int toYClock[9][9] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
  {1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1
  {2, 2, 2, 3, 4, 5, 2, 2, 2}, // 2

  {3, 3, 2, 3, 4, 5, 6, 3, 3}, // 3
  {4, 4, 2, 3, 4, 5, 6, 4, 4}, // 4
  {5, 5, 2, 3, 4, 5, 6, 5, 5}, // 5

  {6, 6, 6, 3, 4, 5, 6, 6, 6}, // 6
  {7, 7, 7, 7, 7, 7, 7, 7, 7}, // 7
  {8, 8, 8, 8, 8, 8, 8, 8, 8} // 8
};

const int toXClock[9][9] = {
// 0  1  2  3  4  5  6  7  8
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, // 0
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, // 1
  {0, 1, 2, 6, 6, 6, 6, 7, 8}, // 2

  {0, 1, 3, 5, 5, 5, 3, 7, 8}, // 3
  {0, 1, 4, 4, 4, 4, 4, 7, 8}, // 4
  {0, 1, 5, 3, 3, 3, 5, 7, 8}, // 5

  {0, 1, 2, 2, 2, 2, 6, 7, 8}, // 6
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, // 7
  {0, 1, 2, 3, 4, 5, 6, 7, 8} // 8
};

const int toYCounter[9][9] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
  {1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1
  {2, 2, 2, 3, 4, 5, 2, 2, 2}, // 2

  {3, 3, 6, 3, 4, 5, 2, 3, 3}, // 3
  {4, 4, 6, 3, 4, 5, 2, 4, 4}, // 4
  {5, 5, 6, 3, 4, 5, 2, 5, 5}, // 5

  {6, 6, 6, 3, 4, 5, 6, 6, 6}, // 6
  {7, 7, 7, 7, 7, 7, 7, 7, 7}, // 7
  {8, 8, 8, 8, 8, 8, 8, 8, 8} // 8
};

const int toXCounter[9][9] = {
// 0  1  2  3  4  5  6  7  8
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, // 0
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, // 1
  {0, 1, 2, 2, 2, 2, 6, 7, 8}, // 2

  {0, 1, 3, 3, 3, 3, 3, 7, 8}, // 3
  {0, 1, 4, 4, 4, 4, 4, 7, 8}, // 4
  {0, 1, 5, 5, 5, 5, 5, 7, 8}, // 5

  {0, 1, 2, 6, 6, 6, 6, 7, 8}, // 6
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, // 7
  {0, 1, 2, 3, 4, 5, 6, 7, 8} // 8
};

void copyFace(char dest[9][9], int row, int col, int which) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      dest[row + i][col + j] = faces[which][i][j];
    }
  }
}

void recoverFace(char src[9][9], int row, int col, int which) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      faces[which][i][j] = src[row + i][col + j];
    }
  }
}

void turn(int face, int d) {
  char temp[9][9], result[9][9];

  memset(temp, '.', sizeof(temp));

  const int fromRow[4] = {
    0, 3, 6, 3 
  };

  const int fromCol[4] = {
    3, 6, 3, 0
  };

  for(int f = 0; f < 4; f++) {
    int whichFace = effectFaces[face][f];
    copyFace(temp, fromRow[f], fromCol[f], whichFace);
  }
  copyFace(temp, 3, 3, face);

  for(int i = 0; i < 9; i++) {
    for(int j = i; j < 9; j++) {
      int t = temp[j][i];
      temp[j][i] = temp[i][j];
      temp[i][j] = t;
    }
  }

  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      int row = d == CLK ? toYClock[i][j] : toYCounter[i][j];
      int col = d == CLK ? toXClock[i][j] : toXCounter[i][j];
      result[row][col] = temp[i][j];
    }
  }

  
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      cout << result[i][j];
    }
    cout << endl;
  }

  

  

  for(int f = 0; f < 4; f++) {
    int whichFace = effectFaces[face][f];
    recoverFace(result, fromRow[f], fromCol[f], whichFace);
  }
  recoverFace(result, 3, 3, face);
    

    
}


void init() {
  for(int c = 0; c < 6; c++) {
    char color = initalFaces[c];
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        faces[c][i][j] = color;
      }
    }
  }
}

void print() {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      cout << faces[U][i][j]; 
    }
    cout << endl;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  while(T--) {
    cin >> n;

    init();    

    int face;
    int d;
    char e;
    for(int i = 0; i < n; i++) {
      cin >> e;
      switch(e) {
        case 'U':
          face = U;
          break;
        case 'D':
          face = D;
          break;
        case 'F':
          face = F;
          break;
        case 'B':
          face = B;
          break;
        case 'L':
          face = L;
          break;
        case 'R':
          face = R;
          break;
        default:
          assert(false);
      }

      cin >> e;
      if(e == '-') d = CCLK;
      else d = CLK;
    
      turn(face, d);
    }

    print();
  }


  return 0;
}
