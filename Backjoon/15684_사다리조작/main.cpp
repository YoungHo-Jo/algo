#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
#define endl '\n'

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

typedef unsigned int ui;
typedef pair<ui, ui> pii;

int main(void) {
  ios::sync_with_stdio(0); cin.tie(0);
  ui N, M, H;
  cin >> N >> M >> H;

  vector<vector<bool>> lines(H+1, vector<bool>(N+1, false));
  for(ui i = 0; i < M; i++) {
    ui h, b;
    cin >> h >> b;
    lines[h][b] = true;
  }
  
  D(
    for(auto& hori: lines) {
      for(auto verti: hori) {
        cout << (verti ? 1 : 0) << " ";
      }
      cout << endl;
    }
  )

  vector<pii> possibleLines;
  for(ui i = 1; i <= H; i++) {
    for(ui j = 1; j < N; j++) {
      if(lines[i][j] == false && lines[i][j - 1] != 1 && lines[i][j + 1] != 1) {
        possibleLines.emplace_back(i, j);
      } 
    }
  }

  D(
    for(auto& e: possibleLines) {
      cout << e.first << " " << e.second << endl;
    }
  )

  auto checkCan = [&N, &H](vector<vector<bool>>& lines, const ui& i) {
    ui verti = i;
    for(ui h = 1; h <= H; h++) {
      if(lines[h][verti] == true) {
        D(cout << "Verti: " << verti << " -> " << verti + 1 << endl;)
        verti++;
      } else if(lines[h][verti - 1] == true) {
        D(cout << "Verti: " << verti << " -> " << verti -1  << endl;)
        verti--;
      }
    }
    return verti == i;
  };

  auto checkValidation = [&N, &H](vector<vector<bool>>& lines) {
    for(ui h = 1; h <= H; h++) {
      for(ui v = 1; v < N; v++) {
        if(lines[h][v] == true && (lines[h][v - 1] == true || lines[h][v + 1])) {
          return false;
        }
      }
    }
    return true;
  };

  ui numOfBeingAbleToAdd = 4;
  for(ui m = 0; m <= 3; m++) {
    if(possibleLines.size() == 0) m = 0;
    vector<bool> mask(possibleLines.size() - m, false);
    for(ui j = 0; j < m; j++) {
      mask.push_back(true);
    }
    D(cout << "Start checking all combiation of lines" << endl;)
    do {
      auto copy = lines;
      for(ui i = 0; i < mask.size(); i++) {
        if(mask[i] == true) {
          auto& l = possibleLines[i];
          copy[l.first][l.second] = true;
        }
      }
      if(!checkValidation(copy)) continue;
      D(cout << "Passed validation" << endl;)
      bool success = true;
      for(ui i = 1; i <= N; i++) {
        if(!checkCan(copy, i)) {
          D(cout << "Failed at: " << i << endl;)
          success = false;
          break;
        }
      }
      if(success) {
        D(cout << "Success: " << m << endl;)
        numOfBeingAbleToAdd = m; 
        break;
      }
    } while(next_permutation(mask.begin(), mask.end()));
    if(numOfBeingAbleToAdd != 4) break;
    if(possibleLines.size() == 0) break;
  }

  if(numOfBeingAbleToAdd == 4) {
    cout << -1 << endl;
  } else {
    cout << numOfBeingAbleToAdd << endl;
  }
  // cout << (numOfBeingAbleToAdd == 3 ? -1 : numOfBeingAbleToAdd) << endl;



  


  return 0;
}