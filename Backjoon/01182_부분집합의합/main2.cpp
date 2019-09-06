#include <iostream>
#include <functional>

using namespace std;

int main(void) {
  int N[20];
  int n, s;
  int ans = 0;
  function<void(int, int)> solve = [&](int index, int sum) {
    if(index == n) {
      ans += sum == s ? 1 : 0;
      return;
    }
    solve(index + 1, sum + N[index]);
    solve(index + 1, sum);
  };

  cin >> n >> s;
  for(int i = 0; i < n; i++) {
    int tmp;
    cin >> tmp;
    N[i] = tmp;
  }
  solve(0, 0);
  ans -= s == 0 ? 1 : 0;
  cout << ans << endl;

  return 0;
}
