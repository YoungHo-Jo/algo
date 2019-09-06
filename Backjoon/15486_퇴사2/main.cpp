#include <iostream>
#include <vector>
#include <utility>
#include <exception>
#include <algorithm>

using namespace std;

using ll = long long;

using pll = pair<ll, ll>;

int main(void) {
  ios::sync_with_stdio(false);
  ll n;
  cin >> n;

  vector<pll> scd(n, pll(0, 0));
  for(ll i = 0; i < n; i++) {
    ll t, p;
    cin >> t >> p;
    scd[i] = pll(t, p); 
  }  

  vector<ll> dp(n, 0);
  for(ll i = 0; i < n; i++) {
    auto& t = scd[i].first;
    auto& p = scd[i].second;
    
    try {
      auto prev = (i == 0) ? 0 : dp.at(i - 1);
      dp[i] = max(prev, dp[i]);
      dp.at(i + t - 1) = max(dp.at(i + t - 1), prev + p);
    } catch(exception& e) {
    }
  }

  cout << dp[n - 1] << endl;

  return 0;
}