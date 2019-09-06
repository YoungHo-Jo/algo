#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define endl '\n'
  
bool maze[5][5][5];
bool cube[5][5][5];

int entranceX[4] = {
  0, 4, 4, 0
};

int entranceY[4] = {
  0, 0, 4, 4
};

void getMaze(const int& at) {
  int inp;
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      cin >> inp; 
      maze[at][i][j] = inp;
    }
  }
}

bool canTopBottomLayer() {
  bool ret = true;
  
  for(int d = 0; d < 4; d++) {
    ret &&= (cube[0][entranceY[d]][entranceX[d]] == false) && 
      (cube[4][entranceY[d]][entranceX[d]] == false);
    if(ret == false) break;
  }

  return ret;
}


// return minimum distance
int solve() {
  // make maze combination 
  // select top layer

  bool cube[5][5][5]; 
  vector<int> order = {
    0, 1, 2, 3, 4  
  };

  do {
    for(auto o: order) {
      cout << o << " ";
    }
    cout << endl;
     
  } while(next_permutation(order.begin(), order.end()));
  
  return 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  for(int i = 0; i < 5; i++) {
    getMaze(i);

  }

  cout << solve() << endl;



  return 0;
}
