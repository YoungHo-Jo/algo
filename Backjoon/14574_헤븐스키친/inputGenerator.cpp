#include <iostream>
#include <ctime>
#include <unordered_map>

using namespace std;

int main(void) {
  int howMany;
  cin >> howMany;

  srand((unsigned int)time(0));

  unordered_map<int, bool> cnt;
  cout << howMany << endl;
  while(cnt.size() < howMany) {
    auto lhs = rand() % (int)1e9 + 1;
    auto rhs = rand() % (int)1e9 + 1;
    if(cnt.find(lhs) == cnt.end()) {
      cnt[lhs] = true;
      cout << lhs << " " << rhs << endl;
    }
  }

  return 0;
}