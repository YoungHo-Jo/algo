#include <iostream>
#include <vector>
using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

const char linked[SWITCHES][CLOCKS + 1] = {
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "xxx...xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    "....xx.x......xx",
    ".xxxxx..........",
    "...xxx...x...x.."
};

bool areAligend(const vector<int>& clocks);

void push(vector<int>& clocks, int swt) {
    for(int clock = 0; clock < CLOCKS; clock++) {
        if(linked[swt][clock] == 'x') {
            clocks[clock] += 3;
            if(clocks[clock] == 15) clocks[clock] = 3;
        }
    }
}

int solve(vector<int>& clocks, int swt) {
    if(swt == SWITCHES) return areAligend(clocks) ? 0 : INF;

    int ret = INF;
    for(int cnt = 0; cnt < 4; cnt++) {
        ret = min(ret, cnt, + solve(clocks, swt + 1));
        push(clocks, swt);
    } 

    return ret;

}


int main(void) {

    int testCaseNum;
    cin >> testCaseNum;

    for(int i = 0; i < testCaseNum; i++) {
        vector<int> clocks;
        for(int j = 0; j < CLOCKS; j++) {
            int time;
            cin >> time;
            clocks.push_back(time);
        }

        cout << solve(clocks, 0) << endl;
    }

    return 0;
}



