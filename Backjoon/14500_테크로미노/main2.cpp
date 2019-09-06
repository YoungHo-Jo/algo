#include <iostream>
#include <vector>
#include <exception>

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

  vector<vector<int>> board(n, vector<int>(m, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int tmp;
      cin >> tmp;
      board[i][j] = tmp;
    }
  }

  auto getType1Hori = [&](int i, int j) {
    try {
      int len = 4;
      int sum = 0;
      for(int s = j; s < j + len; s++) {
        sum += board.at(i).at(s);
      }
      D(cout << "Type 1 Horizontal" << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType1Verti = [&](int i, int j) {
    try {
      int len = 4;
      int sum = 0;
      for(int s = i; s < i + len; s++) {
        sum += board.at(s).at(j);
      }
      D(cout << "Type 1 Vertical" << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType2 = [&](int i, int j) {
    try {
      int len = 2;
      int sum = 0;
      for(int s = i; s < i + len; s++) {
        for(int k = j; k < j + len; k++) {
          sum += board.at(s).at(k);
        }
      }
      D(cout << "Type 2" << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType3Hori = [&](int i, int j, int type) {
    try {
      // clockwise
      // 1: letf up corenr 2: right up corner 3: right down corenr 4: left down corner 
      int len = 3;
      int sum = 0;
      for(int s = j; s < j + len; s++) {
        sum += board.at(i).at(s);
      }
      switch(type) {
        case 1: 
          sum += board.at(i - 1).at(j);
          break;
        case 2:
          sum += board.at(i - 1).at(j + len - 1);
          break;
        case 3:
          sum += board.at(i + 1).at(j + len - 1);
          break;
        case 4:
          sum += board.at(i + 1).at(j);
          break;
      }
      D(cout << "Type 3 Horizontal: " << type << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType3Verti = [&](int i, int j, int type) {
    try {
      int len = 3;
      int sum = 0;
      for(int s = i; s < i + len; s++ ){
        sum += board.at(s).at(j);
      }
      switch(type) {
        case 1: 
          sum += board.at(i).at(j - 1);
          break;
        case 2:
          sum += board.at(i).at(j + 1);
          break;
        case 3:
          sum += board.at(i + len - 1).at(j + 1);
          break;
        case 4:
          sum += board.at(i + len - 1).at(j - 1);
          break;
      }
      D(cout << "Type 3 Vertical: " << type << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType4Verti = [&](int i, int j, int type) {
    try {
      // 1: left up & right down 
      // 2: left down & right up
      int sum = 0;
      sum += board.at(i).at(j) + board.at(i).at(j + 1);
      switch(type) {
        case 1:
          sum += board.at(i - 1).at(j) + board.at(i + 1).at(j + 1);
          break;
        case 2:
          sum += board.at(i + 1).at(j) + board.at(i - 1).at(j + 1);
        break;
      }
      D(cout << "Type 4 Vertical: " << type << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType4Hori = [&](int i, int j, int type) {
    try {
      int sum = 0;
      sum += board.at(i).at(j) + board.at(i + 1).at(j);
      switch(type) {
        case 1:
          sum += board.at(i).at(j - 1) + board.at(i + 1).at(j + 1);
          break;
        case 2:
          sum += board.at(i).at(j + 1) + board.at(i + 1).at(j - 1);
          break;
      }
      D(cout << "Type 4 Horizontal: " << type << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType5Hori = [&](int i, int j, int type) {
    try {
      int len = 3;
      int sum = 0;
      for(int s = j; s < j + len; s++) {
        sum += board.at(i).at(s);
      }
      switch(type) {
        case 1:
          sum += board.at(i - 1).at(j + 1);
          break;
        case 2:
          sum += board.at(i + 1).at(j + 1);
          break;
      }
      D(cout << "Type 5 Horizontal: " << type << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  auto getType5Veri = [&](int i, int j, int type) {
    try {
      int len = 3;
      int sum = 0;
      for(int s = i; s < i + len; s++) {
        sum += board.at(s).at(j);
      }
      switch(type) {
        case 1:
          sum += board.at(i + 1).at(j - 1);
          break;
        case 2:
          sum += board.at(i + 1).at(j + 1);
          break;
      }
      D(cout << "Type 5 Vertical : " << type << endl;)
      return sum;
    } catch(exception& e) {
      return 0;
    }
  };

  int sum = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      D(cout << "i: " << i << " j: " << j << endl;)
      sum = max(sum, getType1Hori(i, j));
      sum = max(sum, getType1Verti(i, j));
      sum = max(sum, getType2(i, j));
      for(int k = 1; k <= 4; k++) {
        if(k <= 2) {
          sum = max(sum, getType4Hori(i, j, k));
          sum = max(sum, getType4Verti(i, j, k));
          sum = max(sum, getType5Hori(i, j, k));
          sum = max(sum, getType5Veri(i, j, k));
        }
        sum = max(sum, getType3Hori(i, j, k));
        sum = max(sum, getType3Verti(i, j, k));
      }
    }
  }

  cout << sum  << endl;

  return 0;
}