#include <iostream>
#include <cstring>
using namespace std;
int n;
bool areFriends[10][10];

int countPairings(bool taken[10]) {
    int firstFree = -1;

    for(int i = 0; i < n; i++) {
        if(!taken[i]) {
            firstFree = i;
            break;
        }
    }

    if(firstFree == -1) return 1;

    int ret = 0;
    for(int pairWith = firstFree + 1; pairWith < n; ++pairWith) {
        if(!taken[pairWith] && areFriends[firstFree][pairWith]) {
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }

    return ret;
}


int main(void) {
    int testCaseNum;
    cin >> testCaseNum;

    for(int i = 0; i < testCaseNum; i++) {
        cin >> n;
        int pairNum;
        cin >> pairNum;

        for(int pairIndex = 0; pairIndex < pairNum; pairIndex++) {
            int lhs, rhs;
            cin >> lhs >> rhs;
            areFriends[lhs][rhs] = true;

        }
        bool taken[10];
        memset(taken, false, sizeof(taken));

        cout << countPairings(taken) << endl;

        memset(areFriends, false, sizeof(areFriends));

    } 

    return 0;
}


