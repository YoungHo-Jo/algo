#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <unordered_set>

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
  // save the cost
  // erase the path edges

  // find 
  // compare the cost
  // if same =? erase
  // if not => return 
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

      vector<piv> dji(N, piv(-1, {}));
      dji[S].first = 0;
      queue<ui> q;
      unordered_set<ui> visited;
      q.push(S);
      visited.insert(S);

      while(q.empty() == false) {
        auto root = q.front();
        D(cout << " root: " << root;)
        q.pop();
        auto found = lower_bound(graph.begin(), graph.end(), root, [](const ppii& lhs, const ui& val){
          return lhs.first.first < val;
        });
        D(cout << " Found: " << *found;)
        if(found->first.first != root) continue;    
        if(root == D) continue;

        for(auto it = found; it != graph.end(); it++) {
          if(it->first.first == root) {
            auto next = it->first.second;
            D(cout << " Next: " << *it;)
            if(visited.find(next) == visited.end()) {
              visited.insert(next);
            }
            D(cout << " dji[root]: " << dji[root].first << " dji[next]: " << dji[next].first;)
            auto sum = it->second + dji[root].first;
            D(cout << " sum: " << sum;)
            if(dji[next].first == -1 || sum < dji[next].first) {
              dji[next].first = sum;
              dji[next].second = dji[root].second;
              dji[next].second.push_back(pii(root, next));
              q.push(next);
            } else if(sum == dji[next].first) {
              D(cout << " sum is same";)
              for(auto e: dji[root].second) {
                dji[next].second.emplace_back(e);
              }
              dji[next].second.emplace_back(pii(root, next));
            }
            D(cout << " ->dji[next]: " << dji[next].first << endl;)
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