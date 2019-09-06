#include <iostream>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef unsigned long long ull;

#define MAX 100000


int main(void) {
  int T;
  cin >> T;
  for(int i = 0; i < T; i++) {
    
    int N;
    cin >> N;
    bitset<MAX> btree;
    vector<int> numVec;
    int num[MAX] = {0, };
    int maxpos = 0;

    for(int j = 0; j < N; j++) {
      int n;
      cin >> n;
      numVec.push_back(n);
      int pos = 1;

      while(true) {
        if(btree[pos] == false) {
          btree[pos] = true;
          num[pos] = n;
          maxpos = max(maxpos, pos);
          cout << pos << endl;
          break;
        } else {
          pos = n < num[pos] ? pos*2 : pos*2 + 1; 
        }
      }
    }

    ull count = 0;
    bitset<MAX> temp;
    memset(num, 0, sizeof(num));
    while(next_permutation(numVec.begin(), numVec.end())) {
      for(auto e: numVec) {
        int pos = 1;
        while(true) {
          if(temp[pos] == false) {
            temp[pos] = true;
            num[pos] = e;
            break;
          } else {
            pos = e < num[pos] ? pos*2 : pos*2 + 1;
          }
        } 
      }

      if(btree == temp) {
        for(auto e: numVec) {
          cout << e << " ";
        }
        cout << endl;
        count++;
      }

      temp.reset();
      memset(num, 0, sizeof(num));
    }
    cout << count << endl;


  } 
  

  return 0;
}