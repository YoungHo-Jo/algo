#include <iostream>
#include <cassert>
#include <stack>
#include <vector>
#include <algorithm>


using namespace std;
  
#define endl '\n'

#ifdef DEBUG
#define D(e) e
#else
#define D(e)
#endif

void setLevel(const string& inp, vector<int>& levels) {

  int level = 0;
  stack<int> st;
  for(int i = 0; i < inp.size(); i++) {
    levels[i] = level;
    
    char c = inp[i];
    if(st.empty() == false) {
      if(st.top() == 1) {
        level--;
        st.pop();
      } else {
        st.top()--;
      }
    }

    if(c == 'x') {
      st.push(4);
      level++;
    }
  }

  assert(st.empty());
  assert(level == 0);
}

string solve(const string& inp, const vector<int>& levels, int s, int e, int level) {
  if(e - s + 1 == 5) {
    D(
      cout << "Solve: base case " << s << " " << e << endl << endl;
    )
    return string{inp[s], inp[s + 3], inp[e], inp[s + 1], inp[e - 2]};
  }
  
  D(
    cout << "Solve: " << s << "~" << e << " level: " << level << endl;
  )

  if(inp[s] == 'x') {
    vector<int> starts;
    
    level++;

    for(int i = s; i <= e; i++) {
      D(
        cout << inp[i] << ":" << i << ":" << levels[i] << " ";
      )

      if(levels[i] == level) {
        starts.push_back(i);
      } 

      if(starts.size() == 4) break;
    }
    D(
      cout << endl;
    )

    assert(starts.size() == 4);

    string upperLeft = solve(inp, levels, starts[0], starts[1] - 1, level);
    string upperRight = solve(inp, levels, starts[1], starts[2] - 1, level);
    string lowerLeft = solve(inp, levels, starts[2], starts[3] - 1, level);
    string lowerRight = solve(inp, levels, starts[3], e, level);


    return string{'x'} + lowerLeft + lowerRight + upperLeft + upperRight;
  } else {
    return string{inp[s]};
  }
}

string mreverse(string::iterator& it) {
  char head = *it;
  ++it;
  if(head == 'b' || head == 'w') {
    return string(1, head);
  } 

  string upperLeft = mreverse(it);
  string upperRight = mreverse(it);
  string lowerLeft = mreverse(it);
  string lowerRight = mreverse(it);
  
  return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;
  while(C--) {
    string inp;
    cin >> inp;
  
    vector<int> levels(inp.size(), 0);
    setLevel(inp, levels);
  
    cout << solve(inp, levels, 0, inp.size() - 1, 0) << endl;
//     cout << mreverse(inp.begin()) << endl;
  }

  return 0;
}
