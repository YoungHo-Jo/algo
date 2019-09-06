#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using namespace std;

#define DEBUG 
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  int n;
  cin >> n;


  vector<vector<int>> map(n, vector<int>(n, 0));
  unordered_set<int> nums;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;
      map[i][j] = tmp;
      nums.insert(tmp);
    }
  }

  function<void(int, int, const int, vector<vector<bool>>&)> dfs = [&](int i, int j, const int& value, vector<vector<bool>>& visited) {
    D(cout << "DFS: " << i << " " << j << endl;)
    if(i < 0 || j < 0 || i >= n || j >= n) {
      D(cout << "Bound with: " << i << " " << j << endl;)
      return;
    }
    if(map[i][j] > value && visited[i][j] == false)  {
      D(cout << "visit: " << i << " " << j << " with: " << value << endl);
      visited[i][j] = true;
      dfs(i - 1, j, value, visited);
      dfs(i, j - 1, value, visited);
      dfs(i, j + 1, value, visited);
      dfs(i + 1, j, value, visited);
    }
  };

  typedef pair<int, vector<vector<bool>>> piv;
  unordered_map<int, piv> checked;
  int maxValue = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      for(auto& num : nums) {
        auto rainHeight = num - 1; 
        D(cout << "======" << endl << "rainheight: " << rainHeight << endl;)
        if(checked.find(rainHeight) == checked.end()) {
          D(cout << "New rainHeight" << endl;)
          checked[rainHeight] = piv(0, vector<vector<bool>>(n, vector<bool>(n, false)));
          if(checked[rainHeight].second[i][j] == false && map[i][j] > rainHeight) checked[rainHeight].first++;
          dfs(i, j, rainHeight, checked[rainHeight].second);
          D(cout << "area: " << checked[rainHeight].first << endl;)
        } else {
          D(cout << "Existed rainHeight" << endl;)
          if(checked[rainHeight].second[i][j] == false && map[i][j] > rainHeight) checked[rainHeight].first++;
          dfs(i, j, rainHeight, checked[rainHeight].second);
          D(cout << "area: " << checked[rainHeight].first << endl;)
        }
        maxValue = max(maxValue, checked[rainHeight].first);
      }
    }
  }
  D(
    for(auto& p: checked) {
      cout << p.first << ": " << p.second.first << endl;
    }
  )

  cout << maxValue << endl;


  return 0;
}