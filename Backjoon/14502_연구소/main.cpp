#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define MAX 8 

// #define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

using pii = pair<int, int>;

int main(void) {
  ios::sync_with_stdio(false);
  
  int N, M;
  cin >> N >> M;
  
  int map[MAX][MAX] = {0, };
  vector<pii> virus;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      int tmp;
      cin >> tmp;
      map[i][j] = tmp; 
      if(tmp == 2) virus.push_back(pii(i, j));
    }
  }  

  function<int()> getSafeArea = [&]() {
    int dummyMap[MAX][MAX];
    memcpy(dummyMap, map, sizeof(map));

    function<void(int, int)> spread = [&](int i, int j) {
      if(i < 0 || i >= N || j < 0 || j >= M) return;
      if(dummyMap[i][j] == 0) {
        dummyMap[i][j] = 2;
        spread(i + 1, j);
        spread(i - 1, j);
        spread(i, j + 1);
        spread(i, j - 1);
      }
    };

    for(auto& v: virus) {
      spread(v.first + 1, v.second);
      spread(v.first - 1, v.second);
      spread(v.first, v.second + 1);
      spread(v.first, v.second - 1);
    }
    
    int safearea = 0;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < M; j++) {
        if(dummyMap[i][j] == 0) safearea++;
      }
    }
    return safearea;
  };


  function<int(int, int, int)> solve = [&](int i, int j, int nWall) {
    D(cout << "Current: " << i << " " << j << " " << nWall << endl;)
    if(i >= N || j >= M || nWall == 0) {
      D(cout << "Bounded" << endl); 
      if(nWall == 0) {
        D(cout << "Calculate space of area" << endl;)
        return getSafeArea();
      }
      return 0;
    }

    int result = 0;
    if(nWall == 0) {
    } else {
      if(map[i][j] == 0) {
        map[i][j] = 1;
        if(j == M - 1) {
          result = max(result, solve(i + 1, 0, nWall - 1));
        } else {
          result = max(result, solve(i, j + 1, nWall - 1));
        }
        map[i][j] = 0;
      }
      if(j == M - 1) {
        result = max(result, solve(i + 1, 0, nWall));
      } else {
        result = max(result, solve(i, j + 1, nWall));
      }
    }
    return result;
  };

  cout << solve(0, 0, 3) << endl;


  return 0;
}