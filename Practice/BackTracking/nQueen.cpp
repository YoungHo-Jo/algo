#include <iostream>
#include <utility>
#include <stack>
#include <vector>

using namespace std;

#define Q 5
typedef unsigned int ui;
typedef pair<ui, ui> pii;
typedef pair<pair<ui, ui>, vector<vector<ui>>> node;


int main(void) {
  auto makeBoard = [](vector<vector<ui>>& board, pii pos) {
    if(board[pos.first][pos.second] != 0) {
      return false;
    }
    ui offset = 1;
    for(ui i = pos.first; i < Q; i++) {
      if(i == pos.first) {
        for(ui j = 0; j < Q; j++) {
            board[i][j] = 1;
        }
      } else {
        auto lhs = pos.second - offset;
        auto rhs = pos.second + offset;
        if(lhs >= 0 && lhs < Q) {
          board[i][lhs] = 1;
        }
        if(rhs < Q && rhs >= 0) {
          board[i][rhs] = 1;
        }
        board[i][pos.second] = 1;
        offset++;
      }
    }
    return true;
  };

  stack<node> bt;
  for(ui i = 0; i < Q; i++) {
    vector<vector<ui>> board(Q, vector<ui>(Q, 0));
    makeBoard(board, pii(0, i));
    bt.push(node(pii(0, i), board));
  }


  ui cnt = 0;
  while(bt.empty() == false) {
    auto top = bt.top();
    auto vertex = top.first;
    auto board = top.second;
    cout << "vertex: " << vertex.first << " " << vertex.second << endl;
    bt.pop();
    if(vertex.first == Q - 1) {
      for(auto row: board) {
        for(auto e: row) {
          cout << e << " ";
        }
        cout << endl;
      }
      cnt++;
      continue; 
    }

    for(ui i = 0; i < Q; i++) {
      cout << "make board: " << vertex.first + 1 << " " << i << endl;
      auto newBoard = board;
      if(makeBoard(newBoard, pii(vertex.first + 1, i))) {
        cout << "can make" << endl;
        bt.push(node(pii(vertex.first + 1, i), newBoard));
      }
    }
  }

  cout << "total: " << cnt << endl;


  
  

  return 0;
}