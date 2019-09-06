#include <iostream>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

#define endl '\n'

int N;

typedef pair<int, int> pii;
typedef pair<double, pii> ppii;
typedef pair<double, double> pdd;

vector<pii> coord;
vector<pii> prop;
vector<bool> alive;
vector<double> impactAt;

#define U 0
#define D 1
#define L 2
#define R 3

bool canReach(const pii& pos, const pii& prop, const pdd& p) {
  switch(prop.first) { 
    case U:
      return pos.first == p.first && pos.second < p.second;
    case D:
      return pos.first == p.first && pos.second > p.second;
    case L:
      return pos.second == p.second && pos.first > p.first;
    case R:
      return pos.second == p.second && pos.first < p.first;
  }
  return false;
}


int solve() {
  // check if cross
  priority_queue<ppii, vector<ppii>, greater<ppii>> pq;
  for(int i = 0; i < coord.size(); i++) {
    for(int j = i + 1; j < coord.size(); j++) {
      const pii& lhs = coord[i];
      const pii& rhs = coord[j];
      const pii& lhsProp = prop[i];
      const pii& rhsProp = prop[j];

      
      if(lhs.first == rhs.first) {
        // same x
        double midYDouble = (double)(lhs.second + rhs.second) / 2;
        
        if(canReach(lhs, lhsProp, pdd(lhs.first, midYDouble)) &&
          canReach(rhs, rhsProp, pdd(rhs.first, midYDouble))) {
          pq.push(ppii(fabs(lhs.second - midYDouble), pii(i, j)));
        }

      } else if(lhs.second == rhs.second) {
        // same y
        double midXDouble = (double)(lhs.first + rhs.first)/2;

        if(canReach(lhs, lhsProp, pdd(midXDouble, lhs.second)) &&
          canReach(rhs, rhsProp, pdd(midXDouble, rhs.second))) {
          pq.push(ppii(fabs(lhs.first - midXDouble), pii(i, j)));
        }
      } else if(((lhsProp.first == U || lhsProp.first == D) && 
                 (rhsProp.first == L || rhsProp.first == R)) || 
                ((lhsProp.first == L || lhsProp.first == R) &&
                 (rhsProp.first == U || rhsProp.first == D))) {
        // otherwise
        // cout << i << " " << j << endl;
        int crossX = (lhsProp.first == U || lhsProp.first == D) ?
          lhs.first : rhs.first;
        int crossY = (lhsProp.first == L || lhsProp.first == R) ?
          lhs.second : rhs.second;
        
        pdd crossP(crossX, crossY); 
        if(canReach(lhs, lhsProp, crossP) &&
          canReach(rhs, rhsProp, crossP)) {

          int lhsTimeToGo = lhsProp.first == U || lhsProp.first == D ?
            abs(crossP.second - lhs.second) : abs(crossP.first - lhs.first);
          int rhsTimeToGo = rhsProp.first == U || rhsProp.first == D ?
            abs(crossP.second - rhs.second) : abs(crossP.first - rhs.first);

          // if cross 
          // push to minheap 
          if(lhsTimeToGo == rhsTimeToGo) {
            pq.push(ppii(lhsTimeToGo, pii(i, j)));
          }
        }
      }
    }
  }
    
  // get energy
  int ret = 0;
  impactAt.assign(coord.size(), 0);
  while(pq.empty() == false) {
    const ppii& top = pq.top();
    const pii& with = top.second;

 //    cout << "at: " << top.first << " with: " << top.second.first << " " << top.second.second << 
 //     " alive: " << alive[with.first] << " " << alive[with.second] << 
 //     " impactAt: " << impactAt[with.first] << " " << impactAt[with.second] << endl;
    if((alive[with.first] && alive[with.second]) ||
      ((alive[with.first] != alive[with.second]) &&
       ((impactAt[with.first] != 0 && impactAt[with.first] == top.first) ||
        (impactAt[with.second] != 0 && impactAt[with.second] == top.first)))) {
       //cout << "impact!" << endl;
      ret += impactAt[with.first] == 0 ? prop[with.first].second : 0;
      ret += impactAt[with.second] == 0 ? prop[with.second].second : 0;
      alive[with.first] = alive[with.second] = false;
      impactAt[with.first] = impactAt[with.second] = top.first;
    } 

    pq.pop();
  }

  
  return ret;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  for(int t = 1; t <= T; t++) {
    coord.clear();
    prop.clear();
    alive.clear();
    impactAt.clear();

    cin >> N;
    int x, y, d, k;
    for(int i = 0; i < N; i++) {
      cin >> x >> y >> d >> k;
      
      coord.push_back(pii(x, y)); 
      prop.push_back(pii(d, k));
      alive.push_back(true);
    }
  
    cout << "#" << t << " " << solve() << endl;
  }



  return 0;
}

