#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template<typename a, typename b>
ostream& operator<<(ostream& os, const pair<a, b>& pai) {
	os << pai.first << ' ' << pai.second;
	return os;
}
template<typename a, typename b>
istream& operator>>(istream& is, pair<a, b>& pai) {
	is >> pai.first >> pai.second;
	return is;
}

#ifdef ONLINE_JUDGE
#define endl '\n'
#endif

#define INF (INT_MAX / 2)

#define MAX_N 50


int n, k;
string arr[MAX_N];
vector<int> picked;

int ans = 0;

void pick(int toPick) {
  cout << "Pick: " << toPick << endl;
	if (picked.size() == k) {
    cout << "picked.size() == k " << k << endl;
		int cnt = 0;
		vector<int> temp = picked;
		sort(temp.begin(), temp.end());
    for(auto t: temp) {
      cout << (char)t << " ";
    }
    cout << endl;

		for (int i = 0; i < n; i++) {
			bool canRead = true;
			for (auto& e : arr[i]) {
        cout << "Find: " << e << endl;
				if (!binary_search(temp.begin(), temp.end(), e)) {
          cout << "not found: " << e << endl;
					canRead = false;
					break;
				}
      }
			if (canRead) {
				++cnt;
        cout << "Canread " << " current: " << cnt << endl;
      }
		}
		ans = max(ans, cnt);
    cout << "Ans: " << ans << endl;

		return;
	}
	if (toPick == 26)
		return;
	if (toPick == 0 || toPick == 2 || toPick == 8 || toPick == 13 || toPick == 19) {
    cout << "topick: " << toPick << endl;
		pick(toPick + 1);
  } else {
    cout << "topick + 'a'" << endl;
		picked.emplace_back(toPick + 'a');
    for(auto p: picked) {
      char c = p;
      cout << c << " ";
    }
    cout << endl;
		pick(toPick + 1);
		picked.pop_back();
		pick(toPick + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string temp;
		cin >> temp;
		arr[i] = temp.substr(4, temp.size() - 8);
    cout << "inp: " << arr[i] << endl;
	}
	picked.emplace_back('a');
	picked.emplace_back('c');
	picked.emplace_back('i');
	picked.emplace_back('n');
	picked.emplace_back('t');

	if (k >= 5)
		pick(0);
	cout << ans << endl;

	return 0;
}