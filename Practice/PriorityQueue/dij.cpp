#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> pii;
typedef pair<ui, vector<ui>> piv;

/*
#OfNodes #OfEdges
Src Des
Edges...(Src Des Cost)
*/

/*
5 8
0 4
0 1 1
0 3 5
1 2 10
1 4 2
2 3 0
3 2 10
3 4 10
4 2 0
*/

int main(void) {
  ui N, E, S, D;
  cin >> N >> E >> S >> D;

  vector<vector<pii>> edges(N, {});
  for(ui i = 0; i < E; i++) {
    ui lhs, rhs, cost;
    cin >> lhs >> rhs >> cost;
    edges[lhs].emplace_back(pii(rhs, cost));
  }

  vector<int> dij(N, INT32_MAX);
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push(pii(0, S));
  dij[S] = 0;
  while(pq.empty() == false) {
    auto here = pq.top().second;
    auto cost = pq.top().first;
    cout << "here: " << here << " cost: " << cost << endl;
    pq.pop();

    for(auto& there: edges[here]) {
      auto thereCost = cost + there.second;
      cout << "thereCost: " << thereCost << endl;
      if(dij[there.first] > thereCost) {
        dij[there.first] = thereCost;
        cout << "Push to pq: " << thereCost << " " << there.first << endl;
        pq.push(pii(thereCost, there.first));
      }
    }
  }

  for(auto& e: dij) {
    cout << e << " ";
  }
  cout << endl;




  return 0;
}
