#include <iostream>
#include <cstring>

using namespace std;

#define endl '\n'

#ifdef DEBUG
#define D(x) cout << " [DEBUG] " << __FUNCTION__ << ":" << __LINE__ << " >> " << x
#else
#define D(x) 
#endif

#define MAX 10

bool isFriend[MAX][MAX];


// Count duplicates
int getCount(int n, bool* taken) {
  bool done = false; 
  for(int i = 0; i < n; i++) {
    if(taken[i] == false) done = false;
  }

  if(done) return 1;

  int ret = 0;

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) { 
      if(!taken[i] && !taken[j] && isFriend[i][j]) {
        D(i << " " << j << " is friend" << endl;)
        taken[i] = taken[j] = true;
        ret += 1 + getCount(n, taken);
        taken[i] = taken[j] = false;
      }
    }  
  }

  return ret;
}

int getNoDuplicateCount(int n, bool* taken) {
  int firstFree = -1;
  
  for(int i = 0; i < n; i++) {
    if(!taken[i]) {
      firstFree = i;
      break;
    }
  }
  

  // base
  // not found free person
  // all set pairs
  if(firstFree == -1) return 1;

  int ret = 0;
  for(int pairWith = firstFree + 1; pairWith < n; pairWith++) {
    if(!taken[pairWith] && isFriend[firstFree][pairWith]) {
      taken[firstFree] = taken[pairWith] = true;
      ret += getNoDuplicateCount(n, taken);
      taken[firstFree] = taken[pairWith] = false;
    }
  }

  return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int testCase;
  cin >> testCase;
  for(int t = 0; t < testCase; t++) {
    int n, m;
    cin >> n >> m; 
    memset(isFriend, 0, sizeof(isFriend));

    for(int i = 0; i < m; i++) {
      int lhs, rhs;
      cin >> lhs >> rhs;
      isFriend[lhs][rhs] = true;  
      isFriend[rhs][lhs] = true;  
    } 
    
    bool taken[MAX] = {false, };
    cout << getNoDuplicateCount(n, taken) << endl;
  }


  return 0;
}

