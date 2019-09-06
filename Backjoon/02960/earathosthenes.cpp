#include <iostream>
#include <vector>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n, k;

  cin >> n >> k;
  
  vector<bool> nums;
  for(int i = 0; i <= n; i++) {
    nums.push_back(true);
  }

  int step = 0;
  while(true) {
    int current = -1; 
    for(int i = 2; i < nums.size(); i++) {
      if(nums[i] == true) {
        current = i;
        break;
      }
    }

    if(current == -1) {
      // cout << "current == -1" << endl;
      break;
    }

    bool isPrime = true;
    for(int i = 2; i < nums.size(); i++) {
      if(current%i == 0 && i != current) {
        // cout << current << " is prime" << endl;
        isPrime = false;
        break;
      }
    }    

    if(isPrime == true) {
      int nToDelete = current;
      while(1 <= nToDelete && nToDelete <= n) {
        if(nums[nToDelete] == false) {
          nToDelete += current;
          continue;
        }
        // cout << "delete " << nToDelete << endl;
        step++;
        nums[nToDelete] = false;
        // cout << "step: " << step << endl;
        if(step == k) {
          cout << nToDelete << endl;
          return 0;
        } else {
          nToDelete += current; 
        }
      }
    } else {
      continue;
    }
  } 

  return 0;
}