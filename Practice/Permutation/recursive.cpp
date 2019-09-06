#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int>& arr, int lhs, int rhs) {
  if(lhs == rhs) return;
  cout << "swap: " << lhs << " " << rhs << endl;
  int temp = arr[lhs];
  arr[lhs] = arr[rhs];
  arr[rhs] = temp;
}

void permutation(vector<int>& arr, int depth) {
  cout << "[" << depth << "]" << endl;
  if(depth == arr.size()) {
    for(auto e: arr) {
      cout << e << " ";
    }
    cout << endl;
    return;
  }

  for(int i = depth; i < arr.size(); i++) {
    swap(arr, i, depth);
    permutation(arr, depth + 1);
    swap(arr, i, depth);
  }
}


int main(void) {
  int n;
  cin >> n;

  vector<int> arr(n, 0);
  for(int i = 0; i < arr.size(); i++) {
    arr[i] = i + 1;
  }

  permutation(arr, 0);
  
  return 0;
}
