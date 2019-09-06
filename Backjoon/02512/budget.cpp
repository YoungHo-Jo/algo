#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int regionNum, budgetOfNation;
vector<int> budgets;

int main(void) {
    cin >> regionNum;

    for(int i = 0; i < regionNum; i++) {
        int req;
        cin >> req;

        budgets.push_back(req); 
    }

    cin >> budgetOfNation;

    sort(budgets.begin(), budgets.end());

    auto sum = [](int upto) {
        int ret = 0;
        for(auto b: budgets) {
            ret += (b <= upto ? b : upto); 
        }
        return ret;
    };

    auto middle = [](int lhs, int rhs) {
        return (lhs + rhs)/2;
    };
    

    int upper = budgets.back() + 1;
    int lower = 0;
    int upto = middle(upper, lower);

    while(true) {
        // cout << "upper: " << upper << " lower: " << lower << endl;
        upto = middle(upper, lower);
        int currentSum = sum(upto);

        if(currentSum > budgetOfNation) {
            upper = upto;
            // cout << "Bigger: " << currentSum << endl;
        } else if (currentSum == budgetOfNation) {
            cout << upto << endl;
            break;
        } else {
            lower = upto;
            // cout << "Smaller: " << currentSum << endl;
        }

        if(lower == upper || abs(upper - lower) == 1) {
            cout << lower << endl; 
            break;
        } 
    }

    return 0;
}