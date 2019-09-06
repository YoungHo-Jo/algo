#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#define MAX 100

int N, M;
int weights[MAX] = {0, };
int cs[MAX] = {0, };
int nums[MAX] = {0, };
int got[MAX] = {0, };
const int INF = -1e9;

int cache[MAX][10001];

int solve(int idx, int curWeight) {
  if(idx >= N || curWeight > M || curWeight > 10001) {
    return INF;
  }
  int& ret = cache[idx][curWeight];
  if(ret != -1) return ret;

  int tmp = 0;
  if(got[idx] < nums[idx]) {
    got[idx]++;
    tmp = max(tmp, solve(idx, curWeight + weights[idx]) + cs[idx]);
    tmp = max(tmp, solve(idx + 1, curWeight + weights[idx]) + cs[idx]);
    got[idx]--;
  }  
  tmp = max(tmp, solve(idx + 1, curWeight));
  ret = tmp; 
  return ret;
}


int main(void) {
  cin >> N >> M;

  memset(weights, 0, sizeof(weights));
  memset(cs, 0, sizeof(weights));
  memset(nums, 0, sizeof(weights));
  memset(got, 0, sizeof(weights));
  memset(cache, -1, sizeof(cache));
  
  int w, n, c;
  for(int i = 0; i < N; i++) {
    cin >> w >> c >> n;
    weights[i] = w;
    cs[i] = c;
    nums[i] = n;
    
  }
  cout << solve(0, 0) << endl;


  return 0;
}