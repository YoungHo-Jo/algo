#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX 1000
using namespace std;

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

vector<vector<int> > costs;
int numberOfHouses;


int main(void) {
    cin >> numberOfHouses;

    for(int i = 0; i < numberOfHouses; i++) {
        vector<int> cost;
        for(int color = 0; color < 3; color++) {
            int temp;
            cin >> temp;
            
            cost.push_back(temp);
        }

        costs.push_back(cost);
    }


    int dp[MAX][3];
    memset(dp, 0, sizeof(dp));

    for(int h = 0; h < numberOfHouses; h++) {
        if(h == 0) {
            dp[h][RED] = costs[h][RED];
            dp[h][GREEN] = costs[h][GREEN];
            dp[h][BLUE] = costs[h][BLUE];
            continue;
        } 

        dp[h][RED] = costs[h][RED] + min(dp[h - 1][GREEN], dp[h - 1][BLUE]);
        dp[h][GREEN] = costs[h][GREEN] + min(dp[h - 1][RED], dp[h - 1][BLUE]);
        dp[h][BLUE] = costs[h][BLUE] + min(dp[h - 1][RED], dp[h - 1][GREEN]);
    }


    cout << min(dp[numberOfHouses - 1][RED], min(dp[numberOfHouses - 1][GREEN], dp[numberOfHouses - 1][BLUE])) << endl;

    

    return 0;
}