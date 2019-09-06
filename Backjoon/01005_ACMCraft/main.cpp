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

    ui W;
    cin >> W;
    W -= 1;

    ui building = W;
    ui totalTime = constTime[W];
    queue<pii> buildingToBuild;
    unordered_set<ui> setToCheck;

    buildingToBuild.push(pii(W, 0));

    auto findToBuild = [&](ui building, ui idx) -> ui {
      auto findRequired = [&building](const pii& pair) {
        return pair.second == building;
      };
      ui max = 0;
      auto required = lower_bound(steps.begin(), steps.end(), building, [](const pii& lhs, const ui rhs) {
        return lhs.second < rhs;
      });
      while(required != steps.end() && required->second == building) {
        D(cout << "Found: " << required->first << " " << required->second << endl;)
        if(setToCheck.find(required->first) == setToCheck.end()) {
          D(cout << "Push to Set: " << required->first << endl;)
          setToCheck.insert(required->first);
          buildingToBuild.push(pii(required->first, idx + 1));
          max = (constTime[required->first] > max) ? constTime[required->first] : max;
          D(cout << "Max: " << max << endl;)
        } 
        steps.erase(required);
        required = lower_bound(steps.begin(), steps.end(), building, [](const pii& lhs, const ui rhs) {
          return lhs.second < rhs;
        });
      }
      return max;
    };

    vector<ui> maxVector(K + 1);

    while(buildingToBuild.empty() == false) {
      pii b = buildingToBuild.front();
      D(cout << "Find max of: " << b.first << endl;)
      ui max = findToBuild(b.first, b.second);
      D(cout << "Current max: " << max << endl;)
      maxVector[b.second] = max > maxVector[b.second] ? max : maxVector[b.second]; 
      buildingToBuild.pop();
    };

    for(auto m: maxVector) {
      D(cout << m << " ";)
      totalTime += m;
    }
    D(cout << endl;)

    D(cout << "total: " << totalTime << endl;)

    
    cout << totalTime << endl;
  }


  return 0;
}