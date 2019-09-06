#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

#define endl '\n'

int board[10][10];

typedef pair<int, int> pii;
typedef pair<int, pii> pipii;

vector<pii> people;
vector<pipii> stairs;
vector<bool> selected; // if the person take second -> true otherwise false

int getTimeToStair(const pii& p, const pii& stair) {
  return abs(p.first - stair.first) + abs(p.second - stair.second);
}

int solve(int nSelect) {
  if(nSelect == people.size()) {
    priority_queue<int, vector<int>, greater<int> > waiting[2];
    // calculate arrival times
    for(int i = 0; i < selected.size(); i++) {
      //cout << selected[i] << " ";
      if(selected[i] == false) {
        // take first stair
        waiting[0].push(getTimeToStair(people[i], stairs[0].second));
      } else {
        waiting[1].push(getTimeToStair(people[i], stairs[1].second));
      }
    }
    
    // simulate waiting time
    int ret = 0;
    for(int i = 0; i < 2; i++) {
      const int& stairTime = stairs[i].first;
      int time = 0;

      queue<int> q;
      while(waiting[i].empty() == false || q.empty() == false) {
        time++;

        while(q.empty() == false) {
          const int& downTime = q.front();
          if(downTime + stairTime <= time) {
            //cout << "done: " << downTime << endl;
            q.pop();
          } else {
            break;
          }
        }

        //cout << "time: " << time << " waiting size: " << waiting[i].size() << endl;
        while(waiting[i].empty() == false) {
          const int& arriveTime = waiting[i].top();
          //cout << "arrive at: " << arriveTime << " current moving: " << q.size() << endl;
          if(arriveTime + 1 <= time && q.size() < 3) {
            //cout << "go down stair" << endl;
            q.push(time); 
            waiting[i].pop(); 
          } else {
            break;
          }
        }
        
      }
      //cout << "i: " << i << " " << time << endl; 
      ret = max(ret, time);
    }
    //cout << ret << endl;

    return ret;
  }

  selected[nSelect] = true;
  int ret = solve(nSelect + 1);
  selected[nSelect] = false;
  ret = min(ret, solve(nSelect + 1));
  
  return ret;
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int tc = 1; tc <= T; tc++) {
    int n;
    cin >> n;
    
    int inp;
    people.clear();
    stairs.clear();
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        cin >> inp;
        if(inp == 1) {
          people.push_back(pii(i, j));
        } else if(inp > 0) {
          stairs.push_back(pipii(inp, pii(i, j)));
        }
      }
    }
    
    
    selected.assign(people.size(), 0);
    cout << "#" << tc << " " << solve(0) << endl; 
  }
}



