#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
 
#define mp make_pair
#define MOD 86400
#define INF 0x7fffffff
#define MAX_SIZE (int)1e5
 
using namespace std;
//ios::sync_with_stdio(false); cin.tie(0);
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<bool> vb;
vii pos;
bool visit[(int)1e3 + 2];
 
int d(pii a, pii b) {
    int x = b.first - a.first;
    int y = b.second - a.second;
 
    return (int)ceil(sqrt(x * x + y * y) / 10);
}
 
bool bfs(int max_cost, int n, int k) {
    memset(visit, 0, sizeof(visit));
 
    queue<pii> q;
    q.push(mp(0, 0)); // from, k
 
    while (!q.empty()) {
        int from = q.front().first;
        int cnt = q.front().second;
        q.pop();
 
        if (from == pos.size() - 1) {
            if (cnt <= k + 1) return 1;
            else return 0;
        }
 
        for (int i = 1; i < pos.size(); i++) {
            if (visit[i]) continue;
 
            if (d(pos[i], pos[from]) <= max_cost) {
                visit[i] = 1;
                q.push(mp(i, cnt + 1));
            }
        }
    }
    
    return 0;
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
 
    int n, k;
    cin >> n >> k;
 
    pos.push_back(mp(0, 0));
 
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
 
        pos.push_back(mp(a, b));
    }
 
    pos.push_back(mp(1e4, 1e4));
 
    int left = 1, right = d(mp(0, 0), mp(1e4, 1e4));
 
    while (left <= right) {
        int mid = (left + right) / 2;
        cout << "left: " << left << " right: " << right << " mid: " << mid << endl;
        
        if (bfs(mid, n, k)) right = mid - 1;
        else left = mid + 1;
    }
 
    cout << left;
 
    return 0;
}
