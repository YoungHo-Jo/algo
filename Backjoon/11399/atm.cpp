#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int peopleNum;
vector<int> mins;



int main(void) {
    cin >> peopleNum;

    for(int i = 0; i < peopleNum; i++) {
        int min;

        cin >> min;

        mins.push_back(min);
    }

    sort(mins.begin(), mins.end());


    int sum = 0;
    int eachSum = 0;
    for(auto m: mins) {
        sum += eachSum + m;
        eachSum += m;
    }
    cout << sum << endl;


    return 0;
}