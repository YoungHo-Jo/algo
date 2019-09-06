#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

const int PLUS = 0;
const int MINUS = 1;
const int MULTI = 2;
const int DIV = 3;

vector<int> nums;
vector<int> operatorsNum;

int numberOfOperations = 0;

int calculate(vector<int>& oper) {
    int ret = nums.front();
    for(int i = 1; i < nums.size(); i++) {
        switch(oper[i - 1]%10) {
            case PLUS:
                ret += nums[i];
                break;
            case MINUS:
                ret -= nums[i];
                break;
            case MULTI:
                ret *= nums[i];
                break;
            case DIV:
                ret /= nums[i];
                break;
        }
    }

    return ret;
}

int main(void) {

    int numberOfNums;
    cin >> numberOfNums;


    // Get numbers
    for(int i = 0; i < numberOfNums; i++) {
        int num;
        cin >> num;

        nums.push_back(num);
    }

    // Get the number of the operations
    for(int i = 0; i < 4; i++) {
        int num;
        cin >> num;

        operatorsNum.push_back(num);
    }

    numberOfOperations = nums.size() - 1;

    vector<int> operPermutation;

    for(auto num = operatorsNum.begin(); num != operatorsNum.end(); num++) {
        for(int i = 0; i < *num; i++) {
            operPermutation.push_back((num - operatorsNum.begin()) + (i + 1)*10);
        }
    }

    sort(operPermutation.begin(), operPermutation.end());

    int max = INT32_MIN, min = INT32_MAX;
    // Caculate
    while(true) {
        int ret = calculate(operPermutation);
        if(ret > max) {
            max = ret;
        }

        if(ret < min) {
            min = ret;
        }
        
        if(!next_permutation(operPermutation.begin(), operPermutation.end())) {
            break;
        } 
    }

    cout << max << endl;
    cout << min << endl;

    return 0;
}