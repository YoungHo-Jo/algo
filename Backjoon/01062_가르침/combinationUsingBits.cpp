#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int main(void) {
  string bitmask = "0000000000000000000000000000000000000000000000000000000000000111";
  do {
    cout << bitmask << endl;
  } while(next_permutation(bitmask.begin(), bitmask.end()));

  return 0;
}