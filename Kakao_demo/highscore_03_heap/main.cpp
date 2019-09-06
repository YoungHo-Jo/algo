#include <string>
#include <vector>
#include <iostream>
#include <queue> 
#include <algorithm>

using namespace std;

typedef int ui;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

vector<int> solution(vector<string> arguments) {
    vector<int> answer;
    auto compareLess = [](const ui *lhs, const ui *rhs) {
      return (*lhs > *rhs) ? true : false; 
    };
    auto compareGreater = [](const ui *lhs, const ui *rhs) {
      return (*lhs > *rhs) ? false : true;
    };
    priority_queue<ui*, vector<ui*>, decltype(compareLess)> minHeap(compareLess);
    priority_queue<ui*, vector<ui*>, decltype(compareGreater)> maxHeap(compareGreater);
    vector<ui*> nums;

    auto insert = [&](ui num) {
      D(cout << "Insert: " << num << endl;)
      ui *newOne = new ui(num); 
      nums.push_back(newOne);
      minHeap.push(newOne);
      maxHeap.push(newOne);
    };

    auto deleteMin = [&]() {
      if(minHeap.size() == 0) {
        return;
      }
      auto min = minHeap.top();
      auto result = find(nums.begin(), nums.end(), min);
      while(result == nums.end() && nums.size() != 0 && minHeap.size() != 0) {
        D(cout << "Already deleted" << endl;)
        minHeap.pop();
        min = minHeap.top();
        result = find(nums.begin(), nums.end(), min);
      }

      D(cout << "Delete from nums" << endl;)
      if(minHeap.size() != 0 && nums.size() != 0) {
        nums.erase(result);
        minHeap.pop();
      }
    };

    auto deleteMax = [&]() {
      if(maxHeap.size() == 0) {
        return;
      }
      auto max = maxHeap.top();
      auto result = find(nums.begin(), nums.end(), max);
      while(result == nums.end() && nums.size() != 0 && maxHeap.size() != 0) {
        D(cout << "Already deleted" << endl;)
        maxHeap.pop();
        max = maxHeap.top();
        result = find(nums.begin(), nums.end(), max);
      }

      D(cout << "Delete from nums" << endl;)
      if(maxHeap.size() != 0 && nums.size() != 0) {
        nums.erase(result);
        maxHeap.pop();
      }
    };

    for(auto s: arguments) {
      string cmd = s.substr(0, 1);
      string num = s.substr(2, s.size() - 2);
      int n = stoi(num);

      if(cmd.compare("I") == 0) {
        D(cout << "cmd: " << cmd << " num: " << num << endl;)
        insert(n);
      } else if(cmd.compare("D") == 0) {
        if(n == 1) {
          deleteMax();
        } else {
          deleteMin();
        }
      }
    }


    int min = INT32_MAX;
    int max = INT32_MIN;
    for(auto n: nums) {
      min = (*n < min) ? *n : min;
      max = (*n > max) ? *n : max;
      delete n;
    }
    answer.push_back(max == INT32_MIN ? 0 : max);
    answer.push_back(min == INT32_MAX ? 0 : min);

    return answer;
}

int main(void) {

  vector<string> i1{
    "I 16", "D 1"
  };

  vector<string> i2{
    "I 7", "I 5", "I -5", "D -1"
  };

  vector<string> i3{
    "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1"
  };


  for(auto n: solution(i1)) {
    cout << n << " ";
  }
  cout << endl;
  for(auto n: solution(i2)) {
    cout << n << " ";
  }
  cout << endl;
  
  for(auto n: solution(i3)) {
    cout << n << " ";
  }
  cout << endl;
  return 0;
}