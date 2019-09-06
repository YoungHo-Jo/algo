#include <iostream>
#include <vector>
#include <functional>
#include <deque>

using namespace std;

#define DEBUG 
#ifdef DEBUG 
#define D(x) x
#else
#define D(x) 
#endif

#define MAX 100

int main(void) {
  ios::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;

  int map[MAX][MAX] = {0, };
  for(int i = 0; i < K; i++) {
    int x, y;
    cin >> x >> y;
    map[x - 1][y - 1] = 1; // apple
  }

  int nComd;
  cin >> nComd;
  using pic = pair<int, char>;

  vector<pic> cmds;
  for(int i = 0; i < nComd; i++) {
    int t;
    char c;
    cin >> t >> c;
    cmds.emplace_back(t, c);
  }

  using pii = pair<int, int>;
  deque<pii> snake;
  snake.push_back(pii(0, 0));
  int t = 0;

  auto checkDone = [&]() {
    auto& head = snake.front();
    if(head.first < 0 || head.first >= N || head.second < 0 || head.second >= N) return true;
    D(cout << "Boundary Checked" << endl;)
    if(map[head.first][head.second] == 2) return true;
    D(cout << "Wall or body checked" << endl;)
    return false;
  };


  int dx[4] = {-1, 0, 1, 0}; // up right down left
  int dy[4] = {0, 1, 0, -1}; // up right down left
  int heading = 1;
  while(checkDone() == false) {
    auto& head = snake.front();
    map[head.first][head.second] = 2;
    D(cout << "Head: " << head.first << " " << head.second << " length of snake: " << snake.size() << endl;)
    if(t == cmds.front().first) {
      D(cout << "Turn the head" << endl;)
      if(cmds.front().second == 'L') {
        heading--;
        heading += heading < 0 ? 4 : 0;
      } else {
        heading++;
        heading %= 4;
      }
      cmds.erase(cmds.begin());
    }
    auto posToGo = pii(head.first + dx[heading], head.second + dy[heading]);
    D(cout << "Position to Go: " << posToGo.first << " " << posToGo.second << endl;)

    snake.push_front(posToGo);
    if(map[posToGo.first][posToGo.second] == 0) {
      D(cout << "No apple.. " << endl;)
      auto& tail = snake.back();
      D(cout << "Bye tail: " << tail.first <<  " " << tail.second << endl;)
      map[tail.first][tail.second] = 0;
      snake.pop_back();
    } else {
      D(cout << "Nammmm Apple!!" << endl;)
    }
    D(
      cout << "Current snake: " << endl;
      for(auto& s: snake) {
        cout << s.first <<  " " << s.second << endl;
      }
      cout << endl;
    )
    t++;    
  } 

  cout << t << endl;
  


  return 0;
}