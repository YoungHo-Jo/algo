#include <iostream>

using namespace std;
#define MAX 100

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

enum Direction {
  Up = 1, Down, Right, Left
};

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);

  int N, L;
  cin >> N >> L;
  
  int map[MAX][MAX] = {0, };

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      int tmp;
      cin >> tmp;
      map[i][j] = tmp;
    }
  }

  auto check = [&](int i, int j, Direction d) {
    // direction
    bool result = true;
    switch(d) {
      case Up:
      if(i - L < 0) {
        result = false;
        break;
      } else {
        for(int s = i - L; s < i; s++) {
          if(map[s][j] != map[i][j] - 1) {
            result = false;
            break;
          }
        }
      }
      break;
      case Down:
      if(i + L >= N) {
        result = false;
        break;
      } else {
        for(int s = i + 1; s < i + L; s++) {
          if(map[s][j] != map[i][j] - 1) {
            result = false;
            break;
          }
        }
      }
      break;
      case Right:
      if(j + L >= N) {
        result = false;
        break;
      } else {
        for(int s = j + 1; s <= j + L; s++) {
          if(map[i][s] != map[i][j] - 1) {
            result = false;
            break;
          }
        }
      }
      break;
      case Left:
      if(j - L < 0) {
        result = false;
        break;
      } else {
        for(int s = j - L; s < j; s++ ) {
          if(map[i][s] != map[i][j] - 1) {
            result = false;
            break;
          }
        }
      }
      break;
    }

    return result;
  };


  int numOfRoutes = 0;
  for(int i = 0; i < N; i++) {
    int prev = map[i][0];
    int prevLedder = -1;
    for(int j = 1; j < N; j++) {
      D(cout << "Current " << i << " " << j << endl;)
      if(map[i][j] - 1 == prev) {
        if((prevLedder == -1 || prevLedder < j - L) && check(i, j, Left)) {
          prevLedder = j - 1;
        } else {
          break;
        }
        D(cout << check(i, j, Left) << endl;)
      } else if(map[i][j] + 1 == prev) {
        if((prevLedder == -1 || prevLedder < j) && check(i, j - 1, Right)) {
          prevLedder = j - 1 + L;
        } else {
          break;
        }
        D(cout << check(i, j - 1, Right) << endl;)
      } else if(map[i][j] == prev) {

      } else {
        break;
      }
      prev = map[i][j];
      if(j == N - 1 && prevLedder) {
        D(cout << "Reach!" << endl;)
        numOfRoutes++;
      }
    }
  }

  for(int j = 0; j < N; j++) {
    int prev = map[0][j];
    int prevLedder = -1;
    for(int i = 1; i < N; i++) {
      D(cout << "Current " << i << " " << j << endl;)
      if(map[i][j] - 1 == prev) {
        if((prevLedder == -1 || prevLedder < i - L) && check(i, j, Up)) {
          prevLedder = i - 1;
        } else {
          break;
        }
        D(cout << check(i, j, Up) << endl;)
      } else if(map[i][j] + 1 == prev) {
        if((prevLedder == -1 || prevLedder < i) && check(i - 1, j, Down)) {
          prevLedder = i - 1 + L;
        } else {
          break;
        }
        D(cout << check(i - 1, j, Down) << endl;)
      } else if(map[i][j] == prev) {

      } else {
        break;
      }
      prev = map[i][j];
      if(i == N - 1) {
        D(cout << "Reach!" << endl;)
        numOfRoutes++;
      } 
    }
  }

  cout << numOfRoutes << endl;
  



  return 0;
}