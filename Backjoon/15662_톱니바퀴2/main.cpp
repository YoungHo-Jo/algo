#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <complex>
#include <functional>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false); 
  
  int n;
  cin >> n;
  vector<bitset<8>> wheels(n);
  
  for(int i = 0; i < n; i++) {
    string line;
    cin >> line;
    wheels[i] = bitset<8>(line);
  } 

  auto spinClockWise = [](bitset<8>& wheel, int num) {
    bitset<8> mask(pow(2, num) - 1);
    mask &= wheel;
    mask <<= (8 - num);
    wheel >>= num;
    wheel |= mask;
  };

  auto spinCounterClockWise = [](bitset<8>& wheel, int num) {
    bitset<8> mask(pow(2, 8) - 1);
    mask ^= bitset<8>(pow(2, 8 - num) - 1);
    mask &= wheel;
    mask >>= (8 - num);
    wheel <<= num;
    wheel |= mask;
  };

  const int rhsPos = 5;
  const int lhsPos = 1;

  int nSpin;
  cin >> nSpin;

  vector<int> comd(n, 0); // 0: nothing, 1: clockwise, -1: counter clockwise
  function<void(const int, const int, const int)> makeCmd = [&](const int& idx, const int prevIdx, const int prevCmd) {
    if(idx < 0 || idx >= n || prevCmd == 0 || prevIdx < 0 || prevIdx >= n) return;
    if(idx < prevIdx && wheels[idx][rhsPos] != wheels[prevIdx][lhsPos]) {
      comd[idx] = prevCmd == 1 ? -1 : 1;
      makeCmd(idx - 1, idx, comd[idx]);
    } 
    if(prevIdx < idx && wheels[prevIdx][rhsPos] != wheels[idx][lhsPos]) {
      comd[idx] = prevCmd == 1 ? -1 : 1;
      makeCmd(idx + 1, idx, comd[idx]);
    }
  };

  for(int i = 0; i < nSpin; i++) {
    comd = vector<int>(n, 0);
    int which, direction;
    cin >> which >> direction;

    which -= 1; // 
    comd[which] = direction;
    makeCmd(which - 1, which, direction);
    makeCmd(which + 1, which, direction);

    for(int j = 0; j < n; j++) {
      if(comd[j] == 1) spinClockWise(wheels[j], 1);
      if(comd[j] == -1) spinCounterClockWise(wheels[j], 1);
    }
  }

  int ans = 0;
  for(auto& w: wheels) {
    if(w[7] == true) ans++;
  }
  cout << ans << endl;

  return 0;
}
