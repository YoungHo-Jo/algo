#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> pii;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif


int main(void) {


  ui T;
  cin >> T;

  for(ui i = 0; i < T; i++) {
    ui N, K;
    cin >> N >> K;
    vector<ui> constTime;
    for(ui j = 0; j < N; j++) {
      ui tmp;
      cin >> tmp;
      constTime.emplace_back(tmp);
    }

    vector<pii> steps;
    for(ui j = 0; j < K; j++) {
      ui prev, next;
      cin >> prev >> next;

      steps.push_back(pii(prev - 1, next - 1));
    }
    
    sort(steps.begin(), steps.end(), [](const pii& lhs, const pii& rhs) {
      return lhs.second < rhs.second;
    });

    D(
      for_each(steps.begin(), steps.end(), [](const pii& e) {
        cout << "from: " << e.first << " to " << e.second  << endl;
      });
    )

    ui W;
    cin >> W;
    W -= 1;

    stack<pii> dfs, sortedTopology;
    unordered_set<ui> setToCheck;  
    dfs.push(pii(W, 0));
    setToCheck.insert(W);

    while(dfs.empty() == false) {
      auto top = dfs.top();
      auto prev = lower_bound(steps.begin(), steps.end(), top.first, [](const pii& lhs, const ui& rhs) {
        return lhs.second < rhs;
      });
      // auto prev = upper_bound(steps.begin(), steps.end(), top.first, [](const ui& lhs, const pii& rhs) {
      //   return lhs <= rhs.second;
      // });
      if(prev->second == top.first && setToCheck.find(prev->first) == setToCheck.end()) {
        dfs.push(pii(prev->first, top.second + 1));
        setToCheck.insert(prev->first);
        D(cout << "Push: " << prev->first << " at: " << top.second + 1 << endl;)
        steps.erase(prev);
      } else {
        D(cout << "Pop: " << dfs.top().first << " at: " << dfs.top().second << endl;)
        sortedTopology.push(dfs.top());
        dfs.pop();
      }
    }


    vector<ui> stepMax(K + 1, 0);
    ui offset = 0;
    ui prev = sortedTopology.top().second;
    while(sortedTopology.empty() == false) {
      auto& top = sortedTopology.top();

      if(prev > top.second && sortedTopology.size() < prev) {
        offset = prev;
        D(cout << "Update offset: " << offset << endl;)
      }
      top.second += offset;
      prev = top.second;

      D(cout << top.second << ": " << top.first << endl;)
      stepMax[top.second] = max(stepMax[top.second], constTime[top.first]);
      sortedTopology.pop();
    }

    ui requiredTime = 0;
    for_each(stepMax.begin(), stepMax.end(), [&requiredTime](const ui& e) {
      D(cout << "max: " << e << endl;)
      requiredTime += e;
    });

    cout << requiredTime << endl;

    
  }


  return 0;
}