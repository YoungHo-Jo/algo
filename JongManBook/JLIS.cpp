#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

int n, m;
int listA[100];
int listB[100];



int cache[101][101];

const long long NEGINF = numeric_limits<long long>::min();

int solve(int curA, int curB) {
  int& ret = cache[curA + 1][curB + 1];
  if(ret !=  -1) return ret;
  
  // A[indexA], B[indexB]가 이미 존재하므로 2개는 항상 있다
  long long a = (curA == -1 ? NEGINF : listA[curA]);
  long long b = (curB == -1 ? NEGINF : listB[curB]);
  long long maxElement = max(a, b);
  ret = 0;
  
  // find next to go
  for(int nextA = curA + 1; nextA < n; nextA++) {
    if(maxElement < listA[nextA])
      ret = max(ret, solve(nextA, curB) + 1);
  }
  
  for(int nextB = curB + 1; nextB < m; nextB++) {
    if(maxElement < listB[nextB]) 
      ret = max(ret, solve(curA, nextB) + 1);
  }

  return ret;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;
  for(int c = 0; c < C; c++) {
    cin >> n >> m;
    memset(cache, -1, sizeof(cache));

    int e;
    for(int i = 0; i < n; i++) {
      cin >> e;
      listA[i] = e;
    }

    for(int i = 0; i < m; i++) {
      cin >> e;
      listB[i] = e;
    }

    cout << solve(-1, -1) << endl;
  
  }



  return 0;
}


