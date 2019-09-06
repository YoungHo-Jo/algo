#include <iostream>
#define N 10000
using namespace std;

bool isSelfNumber[N];

int main() { 

    for(int i = 1; i < N; i++) {
        isSelfNumber[i] = true;
    }
    int sum = 0;
    for(int i = 1; i < N; i++) {
        int n = i;
        sum = n;
        while(n != 0) {
            sum += n % 10;
            n /= 10;
        }
        if(sum < N) {
            isSelfNumber[sum] = false;
        }
    }

    for(int i = 0; i < N; i++) {
        if(isSelfNumber[i]) {
            cout << i << endl;
        }
    }

    return 0;
}