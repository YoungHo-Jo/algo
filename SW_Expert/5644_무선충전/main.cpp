#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define endl '\n'

typedef pair<int, int> pii;
typedef pair<pii, pii> ppii;

int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};


vector<int> board[10][10];
vector<ppii> bc;
vector<bool> occupied;
vector<int> walks[2];
int M, A;

int chargeMax(const pii& a, const pii& b) {
  int maximum = 0;
  const vector<int>& aArea = board[a.first][a.second];
  const vector<int>& bArea = board[b.first][b.second];
  if(aArea.size() == 0 && bArea.size() == 0) return 0;
  
  const vector<int>& lhs = aArea.size() != 0 ? aArea : bArea;
  const vector<int>& rhs = &lhs == &aArea ? bArea : aArea;

  for(int i = 0; i < lhs.size(); i++) {
    int aCanCharge = bc[lhs[i]].second.second;
    int bCanCharge = 0;

    for(int j = 0; j < rhs.size(); j++) {
      if(lhs[i] == rhs[j]) {
        continue;
      }
      bCanCharge = max(bCanCharge, bc[rhs[j]].second.second);
    }
    
    maximum = max(maximum, aCanCharge + bCanCharge);
  }
  
  return maximum;
  
}

int solve() {
  // init
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      board[i][j].clear();
    }
  }
  
  // set range of bc
  for(int i = 0; i < bc.size(); i++) {
    const pii& pos = bc[i].first;
    const pii& prop = bc[i].second;
    
    queue<pii> q;
    queue<int> d;
    q.push(pos);
    d.push(prop.first); // c
    bool discovered[10][10];
    memset(discovered, false, sizeof(discovered));
    discovered[pos.first][pos.second] = true;
    
    while(q.empty() == false) {
      const pii& p = q.front();
      const int& c = d.front();

      board[p.first][p.second].push_back(i);

      if(c >= 1) {
        int row, col;
        for(int di = 1; di < 5; di++) {
          row = dy[di] + p.first;
          col = dx[di] + p.second;
          if(row < 0 || row >= 10 || col < 0 || col >= 10) {
            continue;
          }

          if(discovered[row][col] == false) {
            q.push(pii(row, col));
            d.push(c - 1);
            discovered[row][col] = true;
          }
        }
      }

      q.pop();
      d.pop();
    }
  }
  

  // start walk
  pii a(0, 0);
  pii b(9, 9);
  int chargeSum = 0;
  const vector<int> aWalk = walks[0];
  const vector<int> bWalk = walks[1];
  
  chargeSum = chargeMax(a, b);
  for(int i = 0; i < M; i++) {
    a.first += dy[aWalk[i]]; 
    a.second += dx[aWalk[i]]; 
    b.first += dy[bWalk[i]]; 
    b.second += dx[bWalk[i]]; 

    chargeSum += chargeMax(a, b);
  }
  
  return chargeSum;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int t = 1; t <= T; t++) {
    cin >> M >> A;
    int inp;
    
    walks[0].clear(); 
    for(int i = 0; i < M; i++) {
      cin >> inp;
      walks[0].push_back(inp);
    }

    walks[1].clear();
    for(int i = 0; i < M; i++) {
      cin >> inp;
      walks[1].push_back(inp);
    }
  
    bc.clear();
    int x, y, c, p;
    for(int i = 0; i < A; i++) {
      cin >> x >> y >> c >> p;
      bc.push_back(ppii(pii(y - 1, x - 1), pii(c, p)));
    }
    
    cout << "#" << t << " " << solve() << endl;
  }


  return 0;
}
