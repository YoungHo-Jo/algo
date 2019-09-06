#include <iostream>
#include <utility>
#include <cstring>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#define endl '\n'
#define MAX 1001

typedef pair<int, int> pii;

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  int t;
  cin >> t;
  
  bool board[MAX][MAX] {false, };

  for(int i = 0; i < t; i++) {
    string inp;
    cin >> inp;
    int tutle = 0;
    pii pos(500, 500);
    // memset(board, false, sizeof(board));
    // board[500][500] = true;

    int minW = 500;
    int maxW = 500;
    int minH = 500;
    int maxH = 500;
    for(auto c: inp) {
      auto go = [&](int c) {
        switch(c) {
          case 'F':
            if(tutle == 0) {
              pos.first--;
            } else if(tutle == 90) {
              pos.second++;
            } else if(tutle == 180) {
              pos.first++;
            } else if(tutle == 270) {
              pos.second--;
            }
            // board[pos.first][pos.second] = true;
            break;
          case 'B':
            if(tutle == 0) {
              pos.first++;
            } else if(tutle == 90) {
              pos.second--;
            } else if(tutle == 180) {
              pos.first--;
            } else if(tutle == 270) {
              pos.second++;
            }
            // board[pos.first][pos.second] = true;
            break;
          case 'L':
            tutle -= 90;
            tutle += tutle < 0 ? 360 : 0;
            break;
          case 'R':
            tutle += 90;
            tutle %= 360;
            break;
        }
      };

      D(cout << "Tutle: " << tutle << " pos: " << pos.first << " " << pos.second << endl;)
      go(c);
      D(cout << "After Tutle: " << tutle << " pos: " << pos.first << " " << pos.second << endl;)
      minW = min(minW, pos.second);
      maxW = max(maxW, pos.second);
      minH = min(minH, pos.first);
      maxH = max(maxH, pos.first);
    }
    D(cout << "minW: " << minW << " maxW: " << maxW << " minH: " << minH << " maxH: " << maxH << endl;)
    D(cout << "w: " << maxW - minW << " h: " << maxH - minH << endl;)
    cout << (maxW - minW)*(maxH - minH) << endl;

  }
  
  
  return 0;
}