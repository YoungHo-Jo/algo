#include <iostream>
#include <functional>
#include <utility>

using namespace std;

#define MAX 50
#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;
  
  int map[MAX][MAX] = {0, };
  int dx[4] = {0, -1, 0, 1};
  int dy[4] = {-1, 0, 1, 0};
  int leftSide[4] = {3, 0, 1, 2};
  int backx[4] = {1, 0, -1, 0};
  int backy[4] = {0, -1, 0, 1};

  int x, y, dir;
  cin >> x >> y >> dir;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++ ){
      int tmp;
      cin >> tmp;
      map[i][j] = tmp; 
    }
  }

  auto print = [&]() {
    cout << "Current map: " << endl;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < M; j++) {
        cout << map[i][j] << " ";
      }
      cout << endl;
    } 
    cout << endl;
  };
  
  int ans = 0;
  function<void(int, int, int)> clear = [&](int x, int y, int direction) {
    D(cout << "Current: " << x << " " << y << " " << direction << endl;)
    if(x < 0 || x >= N || y < 0 || y >= M) {
      D(cout << "Bounded" << endl;)
      return;
    }

    D(print();)

    if(map[x][y] == 0) {
      map[x][y] = 2; // cleared
      ans++;
    } else if(map[x][y] == 1) {
      D(cout << "done!" << endl;)
      return;
    }

    auto check = [&](int x, int y, int direction) {
      auto newX = x + dx[direction];
      auto newY = y + dy[direction];
      if(newX < 0 || newX >= N || newY < 0 || newY >= M) return false;
      else if(map[newX][newY] != 0) return false;
      else return true; 
    };

    int newDirection = direction;
    bool found = false;
    do {
      if(check(x, y, newDirection)) {
        found = true;
        break;
      }
      newDirection = leftSide[newDirection];
    } while(newDirection != direction);
    D(cout << newDirection << " " << direction << endl;)
    if(found == false) {
      D(cout << "Go back" << endl;)
      clear(x + backx[newDirection], y + backy[newDirection], newDirection);
    } else {
      D(cout << "Go to clean" << endl;)
      clear(x + dx[newDirection], y + dy[newDirection], leftSide[newDirection]); 
    }
  };

  clear(x, y, dir);
  cout << ans << endl;

  return 0;
}