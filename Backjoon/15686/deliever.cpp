#include <iostream>
#include <vector>

using namespace std;

struct pos {
  int r;
  int c;
  pos(int r, int c): r(r), c(c) {};
};

const int NONE = 0;
const int HOUSE = 1;
const int STORE = 2;

int main(void) {

  // Read input
  // Save # of current stores 
  int N = 0;
  int M = 0;
  vector<pos> houses;
  vector<pos> stores;

  cin >> N >> M;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      int tmp = 0;
      cin >> tmp;
      if(tmp == HOUSE) {
        houses.push_back(pos(i + 1, j + 1));
      } else if(tmp == STORE) {
        stores.push_back(pos(i + 1, j + 1));
      }
    } 
  }
  
  // Compare maximum stores and current stores
  if(M < stores.size()) {
    // 1. current stores over max
    // - Reduce stores 
  } else {
    // 2. current stores not over max
    // - Go to Print 
  }

  // Print Chicken Distance

  

  return 0;
}