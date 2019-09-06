#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define COL 4

int cache[1000000][COL];

int solution(vector<vector<int>> land) {
  int answer = 0;

  memset(cache, 0, sizeof(cache));

  for(int i = 0; i < COL; i++) {
    cache[0][i] = land[0][i];
  }

  for(int i = 1; i < land.size(); i++) {
    for(int j = 0; j < COL; j++) {
      int& here = cache[i][j];

      for(int col = 0; col < COL; col++) {
        if(col != j) {
          here = max(land[i][j] + cache[i - 1][col], here);
        }
      }
    }
  }

  for(int j = 0; j < 4; j++) {
    answer = max(answer, cache[land.size() - 1][j]);
  }

  return answer;
}