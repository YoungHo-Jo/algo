#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int ui;

int main(void) {
  ui N;
  int S;
  cin >> N >> S;

  vector<int> nums;

  for(ui i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    nums.emplace_back(tmp);
  }

  ui cnt = 0;
  vector<bool> mask;
  for(ui i = 1; i <= N; i++) {
    mask = vector<bool>(N - i, false);
    for(ui j = 0; j < i; j++) {
      mask.push_back(true);
    }

    do {
      int sum = 0;
      for(ui i = 0; i < N; i++) {
        if(mask[i] == true) {
          sum += nums[i];
        }
      }
      if(sum == S) {
        cnt++;
      }
    } while(next_permutation(mask.begin(), mask.end()));

    mask.clear();
  }

  cout << cnt << endl;
  

  return 0;
}