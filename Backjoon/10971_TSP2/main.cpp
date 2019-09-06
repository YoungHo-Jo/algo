#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int ui;
int main(void) {
  ui N;
  cin >> N;

  ui costs[10][10] = {0, };
  for(ui i = 0; i < N; i++) {
    for(ui j = 0; j < N; j++) {
      ui tmp;
      cin >> tmp;
      costs[i][j] = tmp;
    }
  }

  vector<ui> path;
  for(ui i = 0; i < N; i++) {
    path.push_back(i);
  }

  ui pathCost = UINT32_MAX;
  do {
    ui cost = 0;
    ui prev = path.front();
    bool canGo = true;
    for(auto n: path) {
      if(n == path.front()) continue;
      if(costs[prev][n] != 0) {
        cost += costs[prev][n];
        prev = n;
      } else {
        canGo = false;
        break;
      }
    }
    if(costs[path.back()][path.front()] != 0) {
      cost += costs[path.back()][path.front()];
    } else {
      canGo = false;
    }

    cost = canGo == false ? UINT32_MAX : cost;

    pathCost = min(pathCost, cost);
  } while(next_permutation(path.begin(), path.end()));
  cout << (pathCost == UINT32_MAX ? 0 : pathCost) << endl;

  return 0;
}