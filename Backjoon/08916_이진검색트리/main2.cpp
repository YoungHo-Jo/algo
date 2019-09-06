#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

typedef unsigned long long ui;


class FastIO {
    int fd, bufsz;
    char *buf, *cur, *end;
    public:
    FastIO(int _fd = 0, int _bufsz = 1 << 20) : fd(_fd), bufsz(_bufsz) {
        buf = cur = end = new char[bufsz];
    }
    ~FastIO() { delete[] buf; }
    bool readbuf() {
        cur = buf;
        end = buf + bufsz;
        while (true) {
            size_t res = fread(cur, sizeof(char), end - cur, stdin);
            if (res == 0) break;
            cur += res;
        }
        end = cur;
        cur = buf;
        return buf != end;
    }
    int readint() {
        while (true) {
            if (cur == end) readbuf();
            if (isdigit(*cur) || *cur == '-') break;
            ++cur;
        }
        bool sign = true;
        if (*cur == '-') {
            sign = false;
            ++cur;
        }
        int ret = 0;
        while (true) {
            if (cur == end && !readbuf()) break;
            if (!isdigit(*cur)) break;
            ret = ret * 10 + (*cur - '0');
            ++cur;
        }
        return sign ? ret : -ret;
    }
};

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif
typedef pair<ui, ui> pii;
int main(void) {

  FastIO f;
  ui T, N;
  T = f.readint();
  vector<pii> btree(pow(2, 21), pii(0, 0));
  for(ui i = 0; i < T; i++) {
    N = f.readint();
    ui maxPos = 0;

    for(ui j = 0; j < N; j++) {
      ui n;
      n = f.readint();
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
    auto getLeftPos = [](ui parent) {
      return parent*2;
    };
    auto getRightPos = [](ui parent) {
      return parent*2 + 1;
    };
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
      auto root = btree[front];
      D(cout << "Current root: " << root.first << " is left: " << isLeft(front) << " is right: " << isRight(front) << endl;)

      toVisit.pop();

      auto leftPos = getLeftPos(front);
      auto rightPos = getRightPos(front);

      if(isLeft(front)) {
        D(cout << "Push left pos to visit: " << leftPos << " : " << getLeft(front).first <<  endl;)
        toVisit.push(leftPos);
      }
      if(isRight(front)) {
        D(cout << "Push right pos to visit: " << rightPos << " : " << getRight(front).first << endl;)
        toVisit.push(rightPos); 
      }

      if(isLeft(front) && isRight(front)) {
        auto numleft = getLeft(front).second + 1;
        auto rightnum = getRight(front).second + 1;
        // auto m = max(numleft, rightnum) + 1;
        auto n = root.second;
        auto m = max(numleft, rightnum);
        auto nr = n - m;
        D(cout << "n: " << n << " m: " << m << " nr: " << nr  << endl;)
        // auto m = min(numleft, rightnum);
        // ui cur = 0;        
        // for(ui i = 1; i <= r; i++) {
        //   ui nHolder = n;
        //   ui rHolder = i;
        //   ui nr = n - i;
        //   ui step = 1;
        //   while(nHolder >= 1) {
        //     step *= nHolder;
        //     nHolder--;
        //   }
        //   while(rHolder >= 1) {
        //     step /= rHolder;
        //     rHolder--;
        //   }
        //   while(nr >= 1) {
        //     step /= nr;
        //     nr--;
        //   }
        //   cur += step;
        // }
        // total *= cur;
        // total &= 9999991;
        while(n > 1) {
          total *= n;
          n--;
        }
        while(m > 1) {
          total /= m;
          m--;
        }
        while(nr > 1) {
          total /= nr;
          nr--;
        }

        D(cout << "Current: " << total << endl;)
      }

      btree[front] = pii(0, 0);
    }

    cout << total%9999991 << endl;
  }

  

  return 0;
}