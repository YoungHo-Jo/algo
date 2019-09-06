#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <stack>

using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> pii;
typedef pair<pii, ui> ppii;
typedef pair<int, vector<pii>> piv;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

template<typename a, typename b>
ostream& operator<<(ostream& os, const pair<a, b>& pai) {
  os << pai.first << " " << pai.second;
  return os;
}

int main(void) {

  // find the shortest path in graph
  // !! There are mulitple pathes...
  // save the cost
  // erase the path edges in multiple pathes
  // After that, find the shortest path in graph

  while(true)  {
    ui N, M, S, D;
    cin >> N >> M;
    if(N == 0) {
      return 0;
    }
    cin >> S >> D;
    
    
    vector<ppii> graph;
    for(ui i = 0; i < M; i++) {
      ui U, V, P;
      cin >> U >> V >> P;

      graph.emplace_back(ppii(pii(U, V), P));

    }
    sort(graph.begin(), graph.end(), [](const ppii& lhs, const ppii& rhs) {
      return lhs.first.first == rhs.first.first ?
        lhs.first.second < rhs.first.second : lhs.first.first < rhs.first.first;
    });

    auto goDji = [&]() -> piv {

      stack<piv> s;
      ui currentCost = 0;
      priority_queue<piv> pq;
      s.push(pii(S, 0));

      while(s.empty() == false) {
        auto root = s.top();
        D(cout << " root: " << root;)
        auto found = lower_bound(graph.begin(), graph.end(), root.first, [](const ppii& lhs, const ui& val){
          return lhs.first.first < val;
        });
        D(cout << " Found: " << *found;)
        if(found->first.first != root.first) continue;  // Not found
        
        if(root.first == D) {
          vector<pii> path;
          
          continue;
        }

        for(auto it = found; it != graph.end(); it++) {
          if(it->first.first == root.first) {
            s.push(pii(it->first.second, root.second + it->second));
          } else {
            break;
          }
        }
      }

      return dji[D];
    };

    auto result = goDji();
    while(graph.empty() == false && result.first != -1) {
      D(
        cout << result.first << endl;
        for(auto n: result.second) {
          cout << n << " ";
        }
        cout << endl;
      )
      for(auto p: result.second) {
        auto found = lower_bound(graph.begin(), graph.end(), p, [](const ppii& lhs, const pii& val) {
          auto edge = lhs.first;
          return edge.first == val.first ? edge.second < val.second : edge.first < val.first;
        });
        if(found->first == p) {
          graph.erase(found);
        }
      }
      auto prevMinPath = result.first;
      result = goDji();
      if(result.first > prevMinPath) {
        break;
      }
    }
    cout << result.first << endl;
  }
  

  return 0;
}