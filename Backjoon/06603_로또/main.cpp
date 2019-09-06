#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
#define NUM_PICK 6
#define endl '\n'

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while(true) {
    int K;
    cin >> K;
    if(K == 0) break;

    vector<int> nums;
    for(int i = 0; i < K; i++) {
      int inp;
      cin >> inp;
      nums.push_back(inp);
    }

    vector<bool> mask(K, false);
    fill(mask.begin() + K - NUM_PICK, mask.end(), true);

    vector<vector<int>> cases;
    do {
      vector<int> con;
      for(int i = 0; i < mask.size(); i++) {
        if(mask[i] == true) {
          con.emplace_back(nums[i]);
        }
      }
      cases.emplace_back(con);
    } while(next_permutation(mask.begin(), mask.end()));
    sort(cases.begin(), cases.end()); 

    for(auto& c: cases) {
      for(auto& n: c) {
        cout << n << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  return 0;
}