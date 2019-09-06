#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

typedef pair<int, int> pii;

list<int> wheels[4];
list<pii> rotateInfo;

int getScore() {
  int ret = 0;
  for(int i = 0; i < 4; i++) {
    ret += wheels[i].front()*(1 << i);
  }

  return ret;
}

void rotate(const int& which, const int& dir, vector<bool>& visit) {
  list<int>& w = wheels[which];

  // check right
  if(which + 1 < 4 && visit[which + 1] == false) {
    list<int>::iterator right = wheels[which + 1].begin();
    list<int>::iterator here = w.begin();
    advance(right, 6);
    advance(here, 2);

    if(*right != *here) {
      visit[which + 1] = true;
      rotate(which + 1, dir * (-1), visit); 
    }
  }
  // check left
  if(which - 1 >= 0 && visit[which - 1] == false) {
    list<int>::iterator left = wheels[which - 1].begin();
    list<int>::iterator here = w.begin();
    advance(left, 2);
    advance(here, 6);

    if(*left != *here) {
      visit[which - 1] = true;
      rotate(which - 1, dir * (-1), visit);
    }
  }

  if(dir == 1) {
    // clockwise
    w.push_front(w.back());
    w.pop_back();  
  } else {
    // counter clockwise
    w.push_back(w.front());
    w.pop_front();
  }
}

int solve(int k) {
  for(list<pii>::iterator it = rotateInfo.begin(); it != rotateInfo.end(); it++) {
    const int& which= it->first;
    const int& dir = it->second;
    vector<bool> visit(4, false); 
    visit[which] = true;
    rotate(which, dir, visit);
  }

  return getScore();
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int tc = 1; tc <= T; tc++) {
    int inp;
    int k;
    cin >> k;
  
    for(int w = 0; w < 4; w++) {
      wheels[w].clear();
      for(int i = 0; i < 8; i++) { 
        cin >> inp;
        wheels[w].push_back(inp);
      }
    }
    
    int dir; 
    rotateInfo.clear();
    for(int i = 0; i < k; i++) {
      cin >> inp >> dir; 
      rotateInfo.push_back(pii(inp - 1, dir));
    }

    cout << "#" << tc << " " << solve(k) << endl;
  }
  return 0;
}
