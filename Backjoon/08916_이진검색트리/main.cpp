#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>

using namespace std;

typedef unsigned int ui;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

typedef pair<ui, ui> pii;
int main(void) {

  ui T, N;
  cin >> T;
  vector<pii> btree(pow(2, 21), pii(0, 0));
  for(ui i = 0; i < T; i++) {
    cin >> N;
    ui maxPos = 0;

    for(ui j = 0; j < N; j++) {
      ui n;
      cin >> n;
      ui pos = 1;
      while(true) {
        if(btree[pos].first == 0) {
          btree[pos].first = n;
          maxPos = max(maxPos, pos);
          break;
        } else {
          btree[pos].second++;
          if(n < btree[pos].first) {
            pos *= 2;
          } else {
            pos *= 2;
            pos += 1; 
          }
        }
      }
    }
    auto getLeft = [&](ui parent) {
      return btree[parent*2];  
    };
    auto getRight = [&](ui parent) {
      return btree[parent*2 + 1];
    };
    auto isLeft = [&](ui p) {
      return getLeft(p).first != 0;
    };
    auto isRight = [&](ui p) {
      return getRight(p).first != 0;
    };

    D(
      cout << "vector size: " << btree.size() << endl;
      cout << "maxpos: " << maxPos << endl;
      for(ui i = 1; i <= maxPos; i++) {
        cout << btree[i].first << " " << btree[i].second << " | "; 
      }
      cout << endl;
    )
    
    ui total = 1;
    queue<ui> toVisit;
    toVisit.push(1);
    while(toVisit.empty() == false) {
      auto front = toVisit.front();
      auto current = btree[front];
      toVisit.pop();
      if(isLeft(front)) {
        D(cout << "mulitple: " << current.second - getLeft(front).second << endl;)
        total *= current.second - getLeft(front).second;
        if(isLeft(front)) {
          toVisit.push(front*2);
        } else {
        }
      }
      if(isRight(front)) {
        if(isLeft(front)) {
          current.second -= getLeft(front).second + 1;
        }
        D(cout << "mulitple: " << current.second - getRight(front).second << endl;)
        total *= current.second - getRight(front).second;
        if(isRight(front)) {
          toVisit.push(front*2 + 1);
        } else {
        }
      }

      // btree[front] = pii(0, 0);
    }

    cout << total << endl;
  }

  

  return 0;
}