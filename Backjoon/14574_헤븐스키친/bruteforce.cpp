#include <iostream>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

ll n, ans_num = 0;
bool win[1001] = {};
vector<pii> answer;
vector<pii> cooker;

void updateAns(vector<pii> _ans,ll _ans_num){
	ans_num = _ans_num;
	answer.clear();
	for(auto it : _ans)
		answer.emplace_back(it.first, it.second);
}

ll rating(pii lhs, pii rhs){
	return (ll)((double)(lhs.second + rhs.second)  / abs(lhs.first - rhs.first));
}

void sol(vector<pii> lose_win, ll h_ans){
	if(h_ans > ans_num && lose_win.size() == n-1)
		updateAns(lose_win, h_ans);
	for(ll here = 0; here < cooker.size()-1 ; ++here){
		if(win[here])	continue;
		for(ll there = here+1 ; there < cooker.size() ; ++there){
			if(win[there])	continue;
			lose_win.emplace_back(here, there);
			win[there] = 1;
			sol(lose_win, h_ans + rating(cooker[here], cooker[there]));
			win[there] = 0;
			lose_win.pop_back();
			lose_win.emplace_back(there, here);
			win[here] = 1;
			sol(lose_win, h_ans + rating(cooker[here], cooker[there]));
			win[here] = 0;
			lose_win.pop_back();
		}
	}
}
	

int main(){
	//ios::sync_with_stdio(false);
	cin >> n;
	bool win[1001] = {};
	for(ll i =0,a,b; i < n ; ++i){
		cin >> a >> b;
		cooker.emplace_back(a,b);
	}
	vector<pii> lose_win;
	sol(lose_win, 0);
	cout << ans_num << "\n";
	for(auto it : answer)
		cout << it.first+1 << " " << it.second+1 << "\n";

	return 0;
}