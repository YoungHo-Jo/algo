#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N, K;
  cin >> N, K;
  vector<vector<int>> map(N, vector<int>(N, 0)); 
  vector<vector<int>> dp(N, vector<int>(N, 0)); 
  vector<vector<int>> dp(N, vector<int>(N, 0)); 
    
  for(int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    map[x - 1][y - 1] = 1;
  }

  function<void() 

  
   

  return 0;
}