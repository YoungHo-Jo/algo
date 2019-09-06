#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<long long, long long> pii;
struct rate;
struct unionFind;
long long n;
pii cookers[1001];
vector<rate> cookers_rate;
vector<int> cookers_adj[1001]; // first : dest, second : rate
bool check[1001] = {};
vector<pii> res;

struct rate{
	long long lhs_index, rhs_index;
	double view_rate;

	rate(long long l_index, long long r_index, pii lhs, pii rhs){
		lhs_index = l_index;
		rhs_index = r_index;
		view_rate = get_viewrate(lhs, rhs);
	}

	long long get_viewrate(pii lhs, pii rhs){
		long long res_rate = (double)(lhs.second + rhs.second) / abs(lhs.first - rhs.first);
		return res_rate;
	}
	bool operator > (const rate& rhs) const{
		return view_rate > rhs.view_rate;
	}
};

struct unionFind{
	vector<int> parent, rank;
	unionFind(int n) : parent(n+1), rank(n+1, 1){
		for(int i = 0 ; i <= n ; ++i)
			parent[i] = i;
	}
	int find(int here){
		if(here == parent[here])	return here;
		return parent[here] = find(parent[here]);
	}
	bool merge(int here, int there){
		here = find(here); there = find(there);
		if(here == there)
			return false;
		if(rank[here] > rank[there])
			swap(here, there);
		parent[here] = there;
		if(rank[here] == rank[there])
			rank[there]++;
		return true;
	}
};

void dfs(int here){
	check[here] = 1;
	for(auto it : cookers_adj[here]){
		if(check[it])
			continue;
		dfs(it);
		res.emplace_back(here, it);
	}
}

void sol(vector<rate> cookers_rate){
	bool ch[1001] = {};
	unionFind unionfind(n);
	long long ans_value = 0;

	for(auto cooker_rate : cookers_rate){
		long long lhs = cooker_rate.lhs_index;
		long long rhs = cooker_rate.rhs_index;
		long long rate = cooker_rate.view_rate;
			
		if(unionfind.merge(lhs,rhs)){
			ans_value += rate;
			cookers_adj[lhs].emplace_back(rhs);
			cookers_adj[rhs].emplace_back(lhs);
		}
	}
	dfs(1);
	cout << ans_value << endl;
	for(auto ans : res)
		cout << ans.first << " " << ans.second << "\n";

}
	


int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1, a, b ; i<= n; ++i){
		cin >> a >> b;
		cookers[i] = {a,b};
	}
	for(long long i = 1 ; i < n ; ++i)
		for(long long j = i+1 ; j <= n ; ++j)
			cookers_rate.emplace_back(i, j, cookers[i], cookers[j]);
	sort(cookers_rate.begin(), cookers_rate.end(), greater<rate>());
	sol(cookers_rate);

	return 0;
}