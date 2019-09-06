#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <cstring>


using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#define E 0
#define C 7
#define T1 1
#define T2 2
#define T3 3
#define T4 4
#define T5 5
#define W 6
#define UP 0
#define RIGHT 90
#define DOWN 180
#define LEFT 270

typedef unsigned int ui;
typedef pair<ui, ui> pi;
typedef pair<pi, ui> ppii;

#define MAX 10
int main(void) {

  ui N, M;
  cin >> N >> M;

  vector<ppii> cctvs;
  vector<ppii> walls;

  for(ui i = 0; i < N; i++) {
    for(ui j = 0; j < M; j++) {
      ui tmp;
      cin >> tmp;
      if(tmp != E && tmp != W) {
        cctvs.push_back(ppii(pi(i, j), tmp));
      } else if(tmp == W) {
        walls.push_back(ppii(pi(i, j), tmp));
      }
    } 
  }

  ui room[MAX][MAX] = {0, };

  auto checkUp = [&](ppii c) {
    for(int i = c.first.first; i >= 0; i--) {
      if(room[i][c.first.second] == E) {
        room[i][c.first.second] = C;
      } else if(room[i][c.first.second] == W) {
        break;
      }
    } 
  };

  auto checkRight = [&](ppii c) {
    for(int i = c.first.second; i < M; i++) {
      if(room[c.first.first][i] == E) {
        room[c.first.first][i] = C;
      } else if(room[c.first.first][i] == W) {
        break;
      }
    } 
  };

  auto checkLeft = [&](ppii c) {
    for(int i = c.first.second; i >= 0; i--) {
      if(room[c.first.first][i] == E){
        room[c.first.first][i] = C;
      } else if(room[c.first.first][i] == W) {
        break;
      }
    }
  };

  auto checkDown = [&](ppii c) {
    for(int i = c.first.first; i < N; i++) {
      if(room[i][c.first.second] == E) {
        room[i][c.first.second] = C;
      } else if(room[i][c.first.second] == W) {
        break;
      }
    }
  };

  auto makeAndCalc = [&](vector<ui> &cases) {
    memset(room, 0, sizeof(room));

    for(auto w: walls) {
      room[w.first.first][w.first.second] = W;
    }

    ui idx = 0;
    for(auto c: cctvs) {
      switch(c.second) {
        case T1:
          if(cases[idx] == UP) {
            checkUp(c);
          } else if(cases[idx] == RIGHT) {
            checkRight(c);
          } else if(cases[idx] == DOWN) {
            checkDown(c);
          } else if(cases[idx] == LEFT) {
            checkLeft(c);
          }
        break;
        case T2:
          if(cases[idx] == UP || cases[idx] == DOWN) {
            checkRight(c);
            checkLeft(c);
          } else if(cases[idx] == RIGHT || cases[idx] == LEFT) {
            checkUp(c);
            checkDown(c);
          }
        break;
        case T3:
          if(cases[idx] == UP) {
            checkUp(c);
            checkRight(c);
          } else if(cases[idx] == RIGHT) {
            checkRight(c);
            checkDown(c);
          } else if(cases[idx] == DOWN) {
            checkDown(c);
            checkLeft(c);
          } else if(cases[idx] == LEFT) {
            checkLeft(c);
            checkUp(c);
          }
        break;
        case T4:
          if(cases[idx] == UP) {
            checkUp(c);
            checkLeft(c);
            checkRight(c);
          } else if(cases[idx] == RIGHT) {
            checkUp(c);
            checkRight(c);
            checkDown(c);
          } else if(cases[idx] == DOWN) {
            checkRight(c);
            checkDown(c);
            checkLeft(c);
          } else if(cases[idx] == LEFT) {
            checkUp(c);
            checkLeft(c);
            checkDown(c);
          }
        break;
        case T5:
          checkUp(c);
          checkLeft(c);
          checkRight(c);
          checkDown(c);
          break;
      }
      idx++;
    }

    ui cnt = 0;
    for(ui i = 0; i < N; i++) {
      for(ui j = 0; j < M; j++) {
        D(cout << room[i][j] << " ";)
        if(room[i][j] == E) {
          cnt++;
        }
      } 
      D(cout << endl; )
    }

    return cnt; 
  };


  vector<ui> cases;
  for(auto c: cctvs) {
    cases.push_back(0);    
  }

  bool isDone = false;
  ui min = makeAndCalc(cases);
  while(!isDone && cases.size() > 0) {
    ui tmp = makeAndCalc(cases);
    min = min > tmp ? tmp : min;
    for(auto it = cases.begin(); it != cases.end(); it++) {
      *it += 90;
      if(*it == 360 && it == cases.end() - 1) {
        isDone = true;
        break;
      } else if(*it == 360) {
        *it = 0; 
      } else {
        break;
      }
    }
    D(
      for(auto e: cases) {
        cout << e << " ";
      } 
      cout << endl;
    )
  }
  cout << min << endl;
  

  return 0;
}