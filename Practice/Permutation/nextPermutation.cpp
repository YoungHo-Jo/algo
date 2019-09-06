#include <iostream>
#include <vector>

using namespace std;

bool nextPermutation(vector<int>::iterator first, vector<int>::iterator last) {
  if(first == last) {
    cout << "nothing in vector" << endl;
    return false; // nothing in vector
  }
  vector<int>::iterator i = last;
  if(first == --i) {
    cout << "vector has only 1 element" << endl;
    return false; // 1 eleemnt
  }
  
  cout << "Start permutation " << endl;
  while(true) {
    vector<int>::iterator i1, i2;
    i1 = i;
    cout << *i << ": " << endl;
    if(*--i < *i1) {
      cout << "i is samller then i1: " << *i << " " << *i1 << endl;

      i2 = last;
      cout << "Find bigger one " << endl;
      while(!(*i < *--i2)) {
        cout << '\t' << *i << " " << *i2 << endl;
      }
      cout << "Swap " << *i << " " << *i2 << endl;
      iter_swap(i, i2);
      cout << "reverse from " << *i1 << " to end" <<  endl;
      reverse(i1, last);
      return true;
    }
    
    if(i == first) {
      cout << "permutation end" << endl; 
      reverse(first, last);
      return false;
    }
  }
}

int main(void) {
  int n;
  cin >> n;
  
  vector<int> arr(n, 0);
  for(int i = 0; i < arr.size(); i++) {
    arr[i] = i + 1;
  }
  
  do {
    for(auto e: arr) {
      cout << e << " ";
    }
    cout << endl;
  } while(nextPermutation(arr.begin(), arr.end()));




  return 0;
}
  

