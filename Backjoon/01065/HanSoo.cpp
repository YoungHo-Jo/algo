/*
어떤 양의 정수 X, 자리수가 등차수열이면 한수
등차수열: 연속된 두 개의 수 차이가 일정한 수열
1 <= X <= N
의 X 개수를 출력하는 문제

입력
첫줄 N <= 1000

출력
첫줄 1 <= 한수 개수 <= N

예제 입력 110
예제 출력 99
*/

#include <iostream>

using namespace std;

bool isHanSoo(int n) {
    int diff = 10;
    int preDigit = 10;
    while(n != 0) {
        int digit = n % 10;
        if (preDigit == 10) { // initial
            preDigit = digit;
        } else if (diff == 10) {
            diff = preDigit - digit;            
            preDigit = digit;
        } else if (preDigit - digit != diff) {
                return false;
        }
        n /= 10;
    }

    return true;
}



int main(void) {
    int inp;

    cin >> inp;

    int hanSooCount = 0;

    for(int i = 1; i <= inp; i++) {
        hanSooCount = (isHanSoo(i)) ?
            hanSooCount + 1 : hanSooCount;
    }

    cout << hanSooCount;

    return 0;
}