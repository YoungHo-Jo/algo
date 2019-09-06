#include <iostream>
#include <utility>
#include <unordered_map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> pii;
typedef pair<ui, pii> pipii;

#define NON '.'

int main(void) {
  ui N;
  cin >> N;

  unordered_map<char, pii> tree;

  for(ui i = 0; i < N; i++) {
    char root, lhs, rhs;
    cin >> root >> lhs >> rhs;
    tree.insert(pipii(root, pii(lhs, rhs)));
  }

  stack<ui> s;
  unordered_map<ui, ui> visited;
  s.push('A');
  string str = "";
  auto visit = [&](const ui& node) {
    visited.insert(pii(node, node));
  };
  auto isVisited = [&](const ui& node) {
    return visited.find(node) != visited.end();
  };
  while(s.empty() == false) {
    if(isVisited(s.top()) == false) {
      str.push_back((char)s.top());
      visit(s.top());
    }
    auto lhs = tree.at(s.top()).first;
    auto rhs = tree.at(s.top()).second;
    if(lhs != NON && isVisited(lhs) == false) {
      s.push(lhs);
    } else if(rhs != NON && isVisited(rhs) == false) {
      s.push(rhs);
    } else {
      s.pop();
    }
  }
  cout << str << endl;

  s.push('A');
  visited.clear();
  str.clear();
  while(s.empty() == false) {
    auto root = s.top();
    auto lhs = tree.at(root).first;
    auto rhs = tree.at(root).second;
    if(lhs != NON && isVisited(lhs) == false) {
      s.push(lhs);
    } else if(rhs != NON && isVisited(rhs) == false) {
      s.push(rhs);
      if(isVisited(root) == false) {
        str.push_back((char)root);
        visit(root);
      }
    } else {
      if(isVisited(root) == false) {
        str.push_back((char)root);
        visit(root);
      }
      s.pop();
    }
  }
  cout << str << endl;

  s.push('A');
  visited.clear();
  str.clear();
  while(s.empty() == false) {
    auto root = s.top();
    auto lhs = tree.at(root).first;
    auto rhs = tree.at(root).second;
    if(lhs != NON && isVisited(lhs) == false) {
      s.push(lhs);
    } else if(rhs != NON && isVisited(rhs) == false) {
      s.push(rhs);
      if(isVisited(root) == false) {
        str.push_back((char)root);
        visit(root);
      }
    } else {
      if(isVisited(root) == false) {
        str.push_back((char)root);
        visit(root);
      }
      s.pop();
    }
  }
  cout << str << endl;
  s.push('A');
  visited.clear();
  str.clear();
  while(s.empty() == false) {
    auto root = s.top();
    auto lhs = tree.at(root).first;
    auto rhs = tree.at(root).second;
    if(lhs != NON && isVisited(lhs) == false) {
      s.push(lhs);
    } else if(rhs != NON && isVisited(rhs) == false) {
      s.push(rhs);
    } else {
      if(isVisited(root) == false) {
       str.push_back((char)root);
        visit(root);
      }
      s.pop();
    }
  }
  cout << str << endl;



  return 0;
}
