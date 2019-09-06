// https://ko.wikipedia.org/wiki/프림_알고리즘
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
7 11
1 2 7
1 4 5
2 3 8
2 5 7
3 5 5
4 2 9
4 5 15
4 6 6
5 6 8
5 7 9
6 7 11
*/

int main(void) {
  int nNodes, nEdges;
  cin >> nNodes >> nEdges;

  vector<vector<int>> graph(nNodes + 1, vector<int>(nNodes + 1, -1));
  for(int i = 0; i < nEdges; i++) {
    int v, u, c;
    cin >> v >> u >> c;
    graph[v][u] = c;
    graph[u][v] = c;
  }

  unordered_map<int, bool> mstVisited;
  mstVisited[4] = true;
  while(mstVisited.size() != nNodes) {
    int minCost = INT32_MAX;
    int minV = 0, minU = 0;
    for(auto& n: mstVisited) {
      for(int i = 1; i <= nNodes; i++) {
          if(graph[n.first][i] != -1 && n.first != i && mstVisited.find(i) == mstVisited.end()
            && minCost >= graph[n.first][i]) {
              minV = n.first;
              minU = i;
              minCost = graph[n.first][i];
          }
      }
    }

    mstVisited[minU] = true;
    cout << minV << " " << minU << endl;
  }

  return 0;
}