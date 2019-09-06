#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


using namespace std;

vector<int> heights;


int main(void) {

    for(int i = 0; i < 9; i++) {
        int h;
        cin >> h;

        heights.push_back(h);
    }

    sort(heights.begin(), heights.end());

    int start = 0;
    int end = 6;


    auto doSomething = [](function<void(int n)> f) {
        for(int i = 0; i < 7; i++) {
            f(heights[i]);
        }
    };


    while(true) {
        int sum = 0;

        doSomething([&sum](int n) {
            sum += n;
        });

        if(sum == 100) {
            doSomething([](int n) {
                cout << n << endl;
            });

            break;
        }

        if(!next_permutation(heights.begin(), heights.end())) {
            doSomething([](int n) {
                cout << n << endl;
            });
        }
    }

    



    return 0;
}