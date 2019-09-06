#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX 300

using namespace std;

const int OEN_STEP = 0;
const int TWO_STEP = 1;
const int NO_MORE = 1;

struct Step {
    int score;
    int count;

    Step(int s, int c) {
        score = s;
        count = c;
    }
};

vector<int> stair;
int stairNum;


int main(void) {
    // Get
    cin >> stairNum;

    for(int i = 0; i < stairNum; i++) {
        int score;
        cin >> score;

        stair.push_back(score);
    }

    int dp[MAX][2], count[MAX];
    memset(dp, 0, sizeof(dp));
    memset(count, 0, sizeof(count));

    for(int s = 0; s < stairNum; s++) {
        if(s == 0) {
            dp[s][OEN_STEP] = stair[s];
            continue;
        } 
        if(s == 1) {
            dp[1][OEN_STEP] = dp[0][OEN_STEP] + stair[1];
            count[1] = NO_MORE; 
            dp[1][TWO_STEP] = stair[1];
            continue;
        }

        if(count[s - 1] != NO_MORE) {
            dp[s][OEN_STEP] = dp[s - 1][OEN_STEP] + stair[s];
            count[s] = NO_MORE;
        } else {
            dp[s][OEN_STEP] = dp[s - 1][TWO_STEP] + stair[s]; 
            count[s] = NO_MORE;
        }

        dp[s][TWO_STEP] = max(dp[s - 2][OEN_STEP], dp[s - 2][TWO_STEP]) + stair[s];
    }

    // for(int i = 0; i < stairNum; i++) {
    //     cout << i << ": " << dp[i][OEN_STEP] << " " << dp[i][TWO_STEP] << endl;
    // }


    cout << max(dp[stairNum - 1][OEN_STEP], dp[stairNum - 1][TWO_STEP]) << endl;
   

    return 0;
}
