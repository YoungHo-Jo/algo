#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
  vector<int> v;
  for(int i = 0; i < 5; i++) {
    v.push_back(i);
  }

  do {
    for(auto e: v) {
      cout << e << " ";
    } 
    cout << endl;
  } while(next_permutation(v.begin(), v.end()));

  return 0;
}