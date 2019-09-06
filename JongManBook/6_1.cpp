#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

#define endl '\n'

static time_t time_now = time(nullptr);
#define INFO cout << put_time(localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [INFO] " << __FILE__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") >> "

long long sum(int n) {
 long long ret = 0;
 for(long long i = 0; i <= n; i++) {
  ret += i;
 }
 return ret;
}

long long recursiveSum(int n) {
 if(n == 1) return 1;
 return n + recursiveSum(n - 1);
}


int main(void)  {
 ios_base::sync_with_stdio(false);
 cin.tie(NULL);
 cout.tie(NULL);

 cout << __cplusplus << endl;

 long long n;
 cout << "Get total sum from 1 to n: " << endl;
 cin >> n;
 
 time_t start;
 start = clock();
 INFO << "for loop: " << sum(n) << endl;
 INFO << "running for " << clock() - start << endl;
 
 start = clock(); 
 INFO << "Recursive: " << recursiveSum(n) << endl;
 INFO << "running for " << clock() - start << endl;


 return 0;
}

