#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <map>
#include <functional>

using namespace std;

// #define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

typedef pair<int, int> pii;
typedef pair<char, int> pci;
typedef pair<pci, pii> dish;

int main(void) {
  ios::sync_with_stdio(false);
  int d, w;
  cin >> d >> w;

  vector<dish> dishes;
  for(int i = 0; i < d; i++) {
    char type;
    int w, ti, dti;
    cin >> type;
    if(type == 'D') {
      cin >> w;
    } else {
      w = 1;
    }
    cin >> ti >> dti;
    dishes.emplace_back(pci(type, w), pii(ti, dti));
  }  

  vector<map<int, double>> dp(d, map<int, double>());
  
  function<double(int, int)> getT = [&](int which, int quantity) {
    auto& type = dishes[which].first.first; 
    auto& ti = dishes[which].second.first;
    auto& dti = dishes[which].second.second;
    if(type == 'D') {
      if(dp[which].find(quantity) == dp[which].end()) {
        double sum = 0;
        for(int i = 1; i <= quantity; i++) {
          sum += ti - (i - 1)*dti; 
        }
        dp[which][quantity] = sum;
      }
      return dp[which][quantity];
    } else {
      return ti*quantity - dti*quantity*quantity*(1/2.0);
    }
  };

  typedef pair<vector<int>, int> pvi;

  // queue<pvi> q;

  auto comp = [&](const pvi& lhs, const pvi& rhs) {
    return lhs.second > rhs.second;
  };
  priority_queue<pvi, vector<pvi>, decltype(comp)> q(comp);
  map<vector<int>, double> checked;
  q.push(pvi(vector<int>(d, 0), 0));

  double ans = 0;
  while(!q.empty()) {
    // auto cur = q.front().first;
    // auto weight = q.front().second;
    auto cur = q.top().first;
    auto weight = q.top().second;
    D(cout << "Current weight: " << weight << endl;)
    q.pop();
    for(int i = 0; i < d; i++) {
      auto node = cur;
      auto newWeight = weight;
      if(node[i] == 0) {
        newWeight += dishes[i].first.second;
        node[i]++;
      } else {
        auto doubling = node[i];
        while(weight + doubling*dishes[i].first.second > w) {
          doubling /= 2;
        }
        newWeight += doubling*dishes[i].first.second;
        node[i] += doubling;
      }

      double sum = 0;
      for(int i = 0; i < d; i++) {
        D(cout << "i: " << i << " " << getT(i, node[i]) << " at: " << node[i] << endl;)
        sum += getT(i, node[i]);
      }
      D(cout << "sum: " << sum << endl;)

      if(checked.find(node) == checked.end() && newWeight <= w && sum > 0) {
        q.push(pvi(node, newWeight));
        checked[node] = sum;
      }
    }

    if(weight == w) {
      ans = max(ans, checked[cur]);
    }
  }

  if(ans == 0) cout << "impossible" << endl;
  else cout << ans << endl;


  return 0;
}