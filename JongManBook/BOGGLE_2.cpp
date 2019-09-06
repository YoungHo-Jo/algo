#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
#define endl '\n'

char board[5][5];

const int dRow[8] = {
  -1, -1, -1,
  0,      0,
  1, 1, 1
};

const int dCol[8] = {
  -1, 0, 1,
  -1,   1,
  -1, 0, 1
};

bool cache[5][5][11];

bool solve(const string& word, int row, int col, int here) {

  // base case
  if(here >= word.size()) return true;
  if(board[row][col] != word[here]) {
    return false;
  }

  // hit
  cache[row][col][here] = true;

  bool ret = false;
  for(int d = 0; d < 8; d++) {
    int toRow = dRow[d] + row;
    int toCol = dCol[d] + col;

    
    if(toRow >= 5 || toCol >= 5 || toRow < 0 || toCol < 0) continue;
    if(cache[toRow][toCol][here + 1]) continue;
 
    ret = solve(word, toRow, toCol, here + 1) || ret;
  }   
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  for(int t = 0; t < T; t++) {
    // Get board
    char c;
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
        cin >> c; 
        board[i][j] = c;
      }
    } 

    // Get words
    int nWord;
    cin >> nWord;
    string s;
    vector<string> words;
    for(int i = 0; i < nWord; i++) {
      cin >> s; 
      words.push_back(s); 
    }

    // Answer
    for(int w = 0; w < words.size(); w++) {
      bool isExist = false;
      memset(cache, false, sizeof(cache));
      for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
          if(solve(words[w], i, j, 0)) {
            isExist = true;
            break;
          }
        }
        if(isExist) {
          break;
        }
      }

      cout << words[w] << " " <<  (isExist ? "YES" : "NO") << endl;
    } 
  }

  return 0;
}