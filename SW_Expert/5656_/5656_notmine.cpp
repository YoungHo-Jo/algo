#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

#ifdef DEBUG
#define D(e) e
#else
#define D(e)
#endif

int map[20][15];
int block[15];
int ans, N, W, H;
int dx[4] = { 0, 0, -1, 1 }; // down up left right
int dy[4] = { -1, 1, 0, 0 }; // down up left right


void init() {
  // reset 
  memset(map, 0, sizeof(map));
  memset(block, 0, sizeof(block));
  N = W = H = 0;
  ans = 0x07777777;
}

int count() {  // why need this??
  int ret = 0;
  for(int j = 0; j < W; j++) { // column
    for(int i = H - 1; i >= 0; i--) { // row from end
      if(map[i][j] >= 1) { 
        ret++;
      } else if (map[i][j] == 0) { // nothing to break
        break;
      }
    }
  }
  

  // 남은 벽돌 수를 리턴
  return ret;
}

bool search(int n) {
  bool ret = false;
  for(int j = 0; j < W; j++) {  
    block[j] = -1;

    for(int i = 0, cnt = 1; i < H; i++) { // start from first row
      if(map[i][j] == 1) cnt++; // no propagation
      else if(map[i][j] > 1) { // if propagation can occur
        if(cnt <= n) ret = true; // propagtaion can occur boolean
        block[j] = cnt; // at j column, break cnt blocks to reach this block
        break;
      }
    }
  }
  
  // return if no propagation block then -1, otherwise the number of 1 blocks to get through
  return ret;
}

typedef struct st {
  int x, y;
} XY;

void BFS(int x, int n) {
  int chk_map[20][15], i;
  int wp = 0, rp = 0, sy, sx, ny, nx;

  XY q[300]; // 20*15

  memset(chk_map, 0, sizeof(chk_map));
  
  // 전처리
  // 여기까지 들어가기위한 1 blcoks 수를 이미 계산해놓고 함수를 불렀기때문에
  // 무시할 것들을 무시하는 과정
  for(i = 0; map[i][x] <= 1; i++) {
    if(map[i][x] == 1) {
      map[i][x] = 0;
    }
  }

  wp = rp = 0;
  sy = q[wp].y = i; // no 1 block's row index
  sx = q[wp].x = x; // from parameter
  wp++;
  rp++;

  chk_map[sy][sx] = 1;
  // BFS
  while(rp <= wp) {
    for(int d = 0; d < 4; d++) {
      int offset = map[sy][sx];
      
      while(offset-- != 1) {
        ny = sy + dy[d] * (map[sy][sx] - offset); // new x 
        nx = sx + dx[d] * (map[sy][sx] - offset); // new y
      
        if(ny < 0 || nx < 0 || ny >= H || nx >= W) continue;
        if(chk_map[ny][nx] != 1 && map[ny][nx] > 1) {  // not visit and more than 1
          q[wp].y = ny;
          q[wp++].x = nx; // push to array to visit
        }
        chk_map[ny][nx] = 1; // mark visit
      }
    }

    sy = q[rp].y; // rp => return point? real point?
    sx = q[rp++].x; 

    // wp will increase if have to visit again because it is not 1 block, it can propagate
    // rp is a working point. always increase
  }

  // clear
  for(int j = 0; j < W; j++) {
    for(int i = 0; i < H; i++) {
      if(chk_map[i][j] == 1) {
        map[i][j] = 0; // clear
      }
    }
  }

  // shrink
  for(int j = 0; j < W; j++) {
    int notZeroCnt = 0;
    for(i = H - 1; i >= 0; i--) { // from bottom to top
      if(map[i][j] >= 1) {
        int highestZeroIdx = H - 1 - notZeroCnt;
        map[highestZeroIdx][j] = map[i][j]; 

        if(highestZeroIdx != i) { 
          map[i][j] = 0;
        }

        notZeroCnt++;
      }
    }
  }
}

void solve(int n) {
  int tempmap[20][15], tempblock[15], num;

  num = count();

  if(num) { // if blocks remain
    if(n == 0) { // no chance to break
      ans = min(ans, num);
      return;
    }

    memcpy(tempblock, block, sizeof(block)); // block to tempblock
    bool isPropataionBlockCanReach = search(n);

    if(isPropataionBlockCanReach == false) { // n >= 1 but can destroy only 1
      if(num - n <= 0) { // 횟수가 많아 다 뿌실수 있을때
        ans = 0;
        return;
      }

      num -= n;
      ans = min(ans, num);
    } else {
      for(int j = 0; j < W; j++) {
        if(block[j] != -1 && block[j] <= n) { // block[j] <= n -> if can go to the propagation block within n times
          memcpy(tempmap, map, sizeof(map)); // copy the status to temp
          BFS(j, block[j]);
          solve(n - block[j]);
          memcpy(map, tempmap, sizeof(map)); // recover the status
        }
      }

      memcpy(block, tempblock, sizeof(block)); // rever the status
    }
  } else { // num == 0
    ans = 0;
  }
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int i, j, tc, T, e;
  cin >> T;

  for(tc = 1; tc <= T; tc++) {
    init();

    cin >> N >> W >> H;
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        cin >> e;
        map[i][j] = e;
      }
    }

    solve(N);
    
    cout << "#" << tc << " " << ans << endl;
  }


  return 0;
}
