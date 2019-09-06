#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

#define endl '\n'
int N, S;

int list[100];
  
int calc(const vector<bool>& s) {
  
  int ret = 0;
  for(int i = 0; i < N; i++) {
    int& n = list[i];
    if(s[n]) continue;
  
    int lhs = n - 1, rhs = n + 1;
    int find = -1;
    while(lhs >= 0 || rhs < s.size()) {
      if(lhs >= 0 && s[lhs]) {
        find = lhs;  
      } else if(rhs < s.size() && s[rhs]) {
        find = rhs;
      }

      lhs--;
      rhs++;

      if(find != -1) break;
    }
    assert(find != -1);
    
    ret += (n - find)*(n - find);
  }

  return ret;
}

int solve(int nS, vector<bool>& s) {
  if(nS > S) return 1e9;
  if(nS == S) return calc(s);
  
  int ret = 1e9;
  for(int i = 1; i < s.size(); i++) {
    if(s[i] == true) continue;
    s[i] = true;
    ret = min(ret, solve(nS + 1, s));
    s[i] = false;
  }

  return ret;
}


// --- BOOK ---
const int INF = 987654321;
int pSum[101];
int pSqSum[101];

// A를 정렬하고 각 부분합을 계산
void precalc() {
  sort(list, list + N);
  pSum[0] = list[0];
  pSqSum[0] = list[0] * list[0];
  for(int i = 1; i < N; i++) {
    pSum[i] = pSum[i - 1] + list[i];
    pSqSum[i] = pSqSum[i - 1] + list[i] * list[i];
  }
}

// A[lo]...A[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합을 계산
int minError(int lo, int hi) {
  int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
  int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
 
  // 평균을 반올림한 값으로 수 들을 표현
  int m = int(0.5 + (double)sum / (hi - lo + 1));

  // sum(A[i] - m)^2를 전개한 결과를 부분 합으로 표현
  int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
  return ret;
}

int cache2[101][11];
int quantize(int from, int parts) {
  // base
  if(from == N) return 0;
  if(parts == 0) return INF;

  int& ret = cache2[from][parts];
  if(ret != -1) return ret;
  ret = INF;

  for(int partSize = 1; from + partSize <= N; partSize++) {
    ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
  }

  return ret;
}


// --- BOOK END ---


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;
  for(int c = 0; c < C; c++) {
    int e;
    cin >> N >> S;
  
    for(int i = 0; i < N; i++) {
      cin >> e;
      list[i] = e;
    }
    
    // vector<bool> s(1001, false);

    // cout << solve(0, s) << endl;
    memset(cache2, -1, sizeof(cache2));
    precalc();
    cout << quantize(0, S) << endl;

  }
  

  return 0;
}
