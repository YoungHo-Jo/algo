#include <iostream>

using namespace std;

#define MAX 501 

#define DEBUG
#ifdef DEBUG 
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  int n, m;
  cin >> n >> m;

  int board[MAX][MAX] = {0, };
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int tmp;
      cin >> tmp;
      board[i][j] = tmp;
    }
  }

  auto getType1Hori = [&](int i, int j) {
    int len = 4;
    if(j + len > m) {
      return 0;
    } 
    int sum = 0;
    for(int s = j; s < j + len; s++) {
      sum += board[i][s]; 
    }
    return sum;
  };

  auto getType1Verti = [&](int i, int j) {
    int len = 4;
    if(i + len > n) {
      return 0;
    }
    int sum = 0;
    for(int s = i; s < i + len; s++) {
      sum += board[s][j];
    }
    D(cout << sum << endl;)
    return sum;
  };

  auto getType2 = [&](int i, int j) {
    int len = 2;
    if(i + len > n || j + len > m) return 0;
    int sum = 0;
    for(int s = i; s < i + len; s++) {
      for(int k = j; k < j + len; k++) {
        sum += board[s][k];
      }
    }
    return sum;
  };

  auto getType3Hori = [&](int i, int j, int type) {
    // clockwise
    // 1: letf up corenr 2: right up corner 3: right down corenr 4: left down corner 
    int len = 3;
    if(j + len > m) return 0;
    int sum = 0;
    for(int s = j; s < j + len; s++) {
      sum += board[i][s];
    }
    switch(type) {
      case 1: 
        if(i - 1 >= 0) sum += board[i - 1][j];
        else return 0;
        break;
      case 2:
        if(i - 1 >= 0) sum += board[i - 1][j + len - 1];
        else return 0;
        break;
      case 3:
        if(i + 1 < n) sum += board[i + 1][j + len - 1];
        else return 0;
        break;
      case 4:
        if(i + 1 < n) sum += board[i + 1][j];
        else return 0;
        break;
    }
    return sum;
  };

  auto getType3Verti = [&](int i, int j, int type) {
    int len = 3;
    if(i + len > m) return 0;
    int sum = 0;
    for(int s = i; s < i + len; s++ ){
      sum += board[s][j];
    }
    switch(type) {
      case 1: 
        if(j - 1 >= 0) sum += board[i][j - 1];
        else return 0;
        break;
      case 2:
        if(j + 1 < m) sum += board[i][j + 1];
        else return 0;
        break;
      case 3:
        if(j + 1 < m) sum += board[i + len - 1][j + 1];
        else return 0;
        break;
      case 4:
        if(j - 1 >= 0) sum += board[i + len - 1][j - 1];
        else return 0;
        break;
    }
    return sum;
  };

  auto getType4Verti = [&](int i, int j, int type) {
    // 1: left up & right down 
    // 2: left down & right up
    if(j + 1 > m) return 0;
    int sum = 0;
    sum += board[i][j] + board[i][j + 1];
    switch(type) {
      case 1:
      if(i - 1 >= 0 && i + 1 < n) {
        sum += board[i - 1][j] + board[i + 1][j + 1];
      } else return 0;
      break;
      case 2:
      if(i - 1 >= 0 && i + 1 < n) {
        sum += board[i][j - 1] + board[i + 1][j + 1];
      } else return 0;
      break;
    }
    return sum;
  };

  auto getType4Hori = [&](int i, int j, int type) {
    if(i + 1 > n) return 0;
    int sum = 0;
    sum += board[i][j] + board[i + 1][j];
    switch(type) {
      case 1:
        if(j - 1 >= 0 && j + 1 < m) {
          sum += board[i][j - 1] + board[i + 1][j + 1];
        } else {
          return 0;
        } 
        break;
      case 2:
        if(j - 1 >= 0 && j + 1 < m) {
          sum += board[i + 1][j - 1] + board[i][j + 1];
        } else {
          return 0;
        } 
        break;
    }

    return sum;
  };

  auto getType5Hori = [&](int i, int j, int type) {
    int len = 3;
    if(j + len > m) return 0;
    int sum = 0;
    for(int s = j; s < j + len; s++) {
      sum += board[i][s];
    }
    switch(type) {
      case 1:
        if(i - 1 >= 0) sum += board[i - 1][j + 1];
        else return 0;
        break;
      case 2:
        if(i + 1 < n) sum += board[i + 1][j + 1];
        else return 0;
        break;
    }
    return sum;
  };

  auto getType5Veri = [&](int i, int j, int type) {
    int len = 3;
    if(i + len > n) return 0;
    int sum = 0;
    for(int s = i; s < i + len; s++) {
      sum += board[s][j];
    }
    switch(type) {
      case 1:
        if(j - 1 >= 0) sum += board[i + 1][j - 1];
        else return 0;
        break;
      case 2:
        if(j + 1 < m) sum += board[i + 1][j + 1];
        else return 0;
        break;
    }
    return sum;
  };

  int sum = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      sum = max(sum, getType1Hori(i, j));
      sum = max(sum, getType1Verti(i, j));
      sum = max(sum, getType2(i, j));
      for(int k = 1; k <= 4; k++) {
        if(i <= 2) {
          sum = max(sum, getType4Hori(i, j, k));
          sum = max(sum, getType4Verti(i, j, k));
          sum = max(sum, getType5Hori(i, j, k));
          sum = max(sum, getType5Veri(i, j, k));
        }
        sum = max(sum, getType3Hori(i, j, k));
        sum = max(sum, getType3Verti(i, j, k));
      }
      D(cout << sum << endl;)
    }
  }

  cout << sum  << endl;

  return 0;
}