#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

using namespace std;

typedef unsigned int ui;

bool solution(vector<string> phone_book) {
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());

    string prev = phone_book.front();
    auto it = phone_book.begin();
    ++it;
    for(; it != phone_book.end(); it++) {
      auto value = it->compare(0, prev.size(), prev);
      if(value == 0) {
        answer = false;
        break;
      } else if(value > 0) {
        prev = *it;
      }
    }

    return answer;
}

int main(void) {


  return 0;
}