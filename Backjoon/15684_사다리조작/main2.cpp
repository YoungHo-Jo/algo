#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

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
        // D(cout << "Verti: " << verti << " -> " << verti + 1 << endl;)
        verti++;
      } else if(lines[h][verti - 1] == true) {
        // D(cout << "Verti: " << verti << " -> " << verti -1  << endl;)
        verti--;
      }
    }
    return verti == i;
  };

  auto checkAll = [&](vector<vector<bool>>& lines) {
    for(ui i = 1; i <= N; i++) {
      if(checkCan(lines, i) == false) return false;
    }
    return true;
  };

  auto canAdd = [&N, &H](vector<vector<bool>>& lines, pii line) {
    D(cout << "Check it can be added: Hori: " << line.first << " Verti: " << line.second << endl;)
    if(lines[line.first][line.second] == false 
      && lines[line.first][line.second - 1] == false 
      && lines[line.first][line.second + 1] == false)
      return true;
    return false;
  };

  D(cout << "Possible line size: " << possibleLines.size() << endl;)
  function<int(ui, ui, vector<vector<bool>>&)> solve = [&](ui index, ui numOfAdded, vector<vector<bool>>& lines) -> int {
    D(cout << "Index: " << index << " numofAdded: " << numOfAdded << endl;)
    if(numOfAdded >= 4) {
      D(cout << "Bounded by the number to be added" << endl;)
      return 4;
    }

    int result = 4;
    if(checkAll(lines)) {
      result = numOfAdded;
    } else {
      if(index >= possibleLines.size()) return result;
      if(numOfAdded >= 3) return result;
      if(canAdd(lines, possibleLines[index])) {
        // vector<vector<bool>> copy(lines); 
        // copy[possibleLines[index].first][possibleLines[index].second] = true;
        lines[possibleLines[index].first][possibleLines[index].second] = true;
        D(cout << "Add: " << possibleLines[index].first << " " << possibleLines[index].second << endl;)
        result = solve(index + 1, numOfAdded + 1, lines);
        D(cout << "AddResult: " << result << endl;)
        lines[possibleLines[index].first][possibleLines[index].second] = false;
      }
      int notAddResult = solve(index + 1, numOfAdded, lines);
      D(cout << "notAddResult: " << notAddResult << endl;)
      result = min(result, notAddResult);
      D(cout << "Result: " << result << endl;)
    }
    return result;
  };
  int ans = solve(0, 0, lines);

  cout << (ans == 4 ? -1 : ans) << endl;



  


  return 0;
}