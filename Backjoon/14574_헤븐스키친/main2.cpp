#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

#define MAX 1001

// #define DBG
#ifdef DBG
#define D(x) x
#else
#define D(x)
#endif

typedef int ui;
typedef pair<ui, ui> pii;
typedef pair<ui, pii> pipii;

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  int n;
  cin >> n;

  vector<pii> cooks(n);
  for(int i = 0; i < n; i++) {
    ui p, c;
    cin >> p >> c;
    cooks[i] = pii(p, c);
  }

  ui dp[MAX][MAX] = {0, };
  vector<pipii> edgesWithCost;
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      dp[i][j] = (cooks.at(i).second + cooks.at(j).second)/abs(cooks.at(i).first - cooks.at(j).first);
      dp[j][i] = dp[i][j];
      edgesWithCost.emplace_back(dp[i][j], pii(i, j)); 
    }
  }

  sort(edgesWithCost.begin(), edgesWithCost.end(), [](const pipii& lhs, const pipii& rhs) {
    return lhs.first > rhs.first;
  });

  D(
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }
  )

  int nContest = n - 1;
  int result = 0;
  vector<pii> mst;
  int matchedCook[MAX] = {false, };
  int matchCount[MAX] = {0, };
  matchedCook[0] = true;

  // For union find
  // int parent[MAX];
  // for(int i = 0; i < n; i++) {
  //   parent[i] = i; 
  // }

  // Prim
  while(nContest > 0) {
    D(
      cout << "matchedCook: " << endl;
      for(int i = 0; i < n; i++) {
        cout << i << "(" << matchedCook[i] << ") ";
      }
      cout << endl;
    )
    
    int maxWatching = 0;
    int lhs = 0, rhs = 0;
    for(int i = 0; i < n; i++) {
      if(matchedCook[i]) {
        for(int j = 0; j < n; j++) {
          if(dp[i][j] >= maxWatching && matchedCook[j] == false && i != j) {
            maxWatching = dp[i][j];
            lhs = i;
            rhs = j;
          }
        }
      }
    }

    matchedCook[rhs] = true;
    mst.emplace_back(lhs, rhs);
    result += maxWatching;
    matchCount[lhs]++;
    matchCount[rhs]++;


    // For union find
    // parent[rhs] = lhs;

    nContest--;
  }

  // Kruskal // Not working correctly
  // bool node[MAX] = {false, };
  // for(auto& e: edgesWithCost) {
  //   auto& lhs = e.second.first;
  //   auto& rhs = e.second.second;
  //   D(cout << lhs << "-" << rhs << endl;)

  //   auto cycle = false;

  //   int curNode = lhs;
  //   bool visited[MAX] = {false, };
  //   while(true) {
  //     D(cout << "Curnode: " << curNode << endl;)
  //     auto found = find_if(mst.begin(), mst.end(), [&](const pii& m) {
  //       return !visited[m.first] && !visited[m.second] && (m.first == curNode || m.second == curNode);
  //     });

  //     if(found != mst.end()) {
  //       D(cout << "Found: " << found->first << " " << found->second << endl;)
  //       visited[curNode] = true;
  //       curNode = (found->first == curNode) ? found->second : found->first;
  //     } else {
  //       break;
  //     }
  //     if(curNode == rhs || found->first == rhs || found->second == rhs) {
  //       cycle = true;
  //       break;
  //     }
  //   }

  //   if(cycle == false) {
  //     D(cout << "Add to mst" << endl;)
  //     mst.push_back(pii(lhs, rhs));
  //     matchCount[lhs]++;
  //     matchCount[rhs]++;
  //     result += e.first;
  //   }
  //   if(mst.size() == n - 1) break;
  // }

  bool isExist[MAX] = {false, };
  D(
    sort(mst.begin(), mst.end());
    for(auto& m: mst) {
      cout << m.first << " " << m.second << endl;
      isExist[m.first] = true;
      isExist[m.second] = true;
    }

    cout << "Not exist" << endl;
    for(int i = 0; i < n; i++) {
      if(isExist[i] == false) {
        cout << i << " ";
      }
    }
    cout << endl;

    int sum = 0;
    cout << "Match count" << endl;
    for(int i = 0; i < n; i++) {
      cout << matchCount[i] << " ";
      sum += matchCount[i];
    }
    cout << endl << "Sum: " << sum << endl;
  )


  cout << result << endl;
  // while(mst.size() > 0) {
  //   auto curNode = mst.front().first;
  //   auto curEdge = mst.begin();
  //   auto found = mst.begin();
  //   do {
  //     found = find_if(mst.begin(), mst.end(), [&](const pii& m) {
  //       return m != *curEdge && (curNode == m.first || curNode == m.second);
  //     });

  //     if(found != mst.end()) {
  //       curEdge = found;
  //       curNode = curNode == curEdge->first ? curEdge->second : curEdge->first;
  //     }
  //   } while(found != mst.end());

  //   D(cout << "Found: " << curEdge->first << " " << curEdge->second << " curNode: " << curNode << endl;)
  //   cout << (curNode == curEdge->first ? curEdge->second : curEdge->first) + 1 << " " << curNode + 1 << endl;
  //   mst.erase(curEdge);
  // }


  // int startNode = 0;
  // bool nodeVisited[MAX] = {false, };
  // bool allVisited = false;

  // while(allVisited == false) {
  //   allVisited = true;
  //   int notVisited = 0;
  //   for(int i = 0; i < n; i++) {
  //     if(nodeVisited[i] == false) {
  //       notVisited = i;
  //       allVisited = false;
  //       break;
  //     }
  //   }

  //   if(allVisited == false) {
  //     while(parent[notVisited] != notVisited) {
  //       cout << parent[notVisited] + 1 << " " << notVisited + 1 << endl;
  //       nodeVisited[notVisited] = true;
  //       notVisited = parent[notVisited];
  //     }
  //     nodeVisited[notVisited] = true;
  //   }
  // }  



  // ======= // 
  // vector<pii> output;  
  // while(mst.size() > 0) {
  //   int foundCount1 = -1;

  //   for(int i = 0; i < n; i++) {
  //     if(matchCount[i] == 1) {
  //       foundCount1 = i;
  //       D(cout << "Found: " << foundCount1 << endl;)
  //       break;
  //     }
  //   }

  //   auto foundEdge = find_if(mst.begin(), mst.end(), [&](const pii& m){
  //     return m.first == foundCount1 || m.second == foundCount1;
  //   });

  //   cout << (foundEdge->first == foundCount1 ? foundEdge->second : foundEdge->first) + 1 << " " << foundCount1 + 1 << endl;
  //   output.emplace_back((foundEdge->first == foundCount1 ? foundEdge->second : foundEdge->first) + 1, foundCount1 + 1);
  //   matchCount[foundEdge->first]--;
  //   matchCount[foundEdge->second]--;
  //   mst.erase(foundEdge);
  // }

  // int winCnt[MAX] = {0, };
  // int loseCnt[MAX] = {0, };
  // D(
  //   cout << "Start checking " << endl;
  //   for(int i = 0; i < output.size(); i++) {
  //     auto& cur = output[i];
  //     winCnt[cur.second]++;
  //     loseCnt[cur.first]++;
  //     for(int j = i + 1; j < output.size(); j++) {
  //       if(output[j].first == cur.second) {
  //         cout << "Lose after gone: " << cur.second << endl;
  //       } 
  //     }
  //   }
  //   int sum2 = 0;
  //   cout << "Win count: " << endl;
  //   for(int i = 1; i <= n; i++) {
  //     cout << winCnt[i] << " ";
  //     sum2 += winCnt[i];
  //   }
  //   cout << endl << "sum2: " << sum2 << endl;
  //   sum2 = 0;
  //   cout << "Lose count: " << endl;
  //   for(int i = 1; i <= n; i++) {
  //     cout << loseCnt[i] << " ";
  //     sum2 += loseCnt[i];
  //   }
  //   cout << endl << "sum2: " << sum2 << endl;
  // )


  // ===== //
  int cnt = 0;
  function<void(int)> solve = [&](int node) {
    D(cout << "Node: " << node << endl;)
    auto found = mst.end();
    do {
      found = find_if(mst.begin(), mst.end(), [&](const pii& m) {
        return m.first == node || m.second == node; 
      });

      if(found != mst.end()) {
        D(cout << "Found: " << found->first << " " << found->second << endl;)
        auto copy = *found;
        D(cout << "erase" << endl;)
        found->first = -1;
        found->second = -1;
        // mst.erase(found);
        solve(copy.first == node ? copy.second : copy.first);
        D(cout << "Count: " << cnt << endl;)
        cnt++;
        cout << node + 1<< " " << (copy.first == node ? copy.second : copy.first) + 1<< endl;
      }
    } while(found != mst.end());
  };

  solve(0);


  return 0;
}