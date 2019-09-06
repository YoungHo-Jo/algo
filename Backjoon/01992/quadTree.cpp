#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <tuple>
#include <queue>


using namespace std;

vector<vector<bool> > image;
int imageSize;



int main(void) {
    cin >> imageSize;

    for(int i = 0; i < imageSize; i++) {
        vector<bool> row;
        string r;

        cin >> r;

        for(int j = 0; j < imageSize; j++) {
            row.push_back(r[j] == '1' ? true : false);
        }
        image.push_back(row);
    }

    enum class State {
        BLACK,
        WHITE,
        MIX
    }; 

    auto check = [](int y, int x, int size) {
        bool previous = image[y][x];
        for(int i = y; i < y + size; i++) {
            for(int j = x; j < x + size; j++) {
                if(previous != image[i][j]) {
                    return State::MIX;
                }
            }
        }

        if(previous == true) {
            return State::BLACK;
        } else if(previous == false) {
            return State::WHITE;
        }
    };

    stack<tuple<int, int, int> > container;
    container.push(make_tuple(0, 0, imageSize));
     
    while(container.empty() == false) {
        auto t = container.top();
        int x = get<0>(t);
        int y = get<1>(t);
        int size = get<2>(t);

        container.pop();
        // cout << "x: " << x << " y: " << y << " size: " << size << endl;

        auto s = check(y, x, size);
        switch(s) {
        case State::MIX:
            // cout << "mix" << endl;
            cout << "(";
            
            size /= 2;
            container.push(make_tuple(x + size, y + size, size));
            container.push(make_tuple(x, y + size, size));
            container.push(make_tuple(x + size, y, size));
            container.push(make_tuple(x, y, size));
            break;
        case State::BLACK:
            // cout << "black" << endl;
            cout << "1";
            break;
        case State::WHITE:
            // cout << "white" << endl;
            cout << "0";
            break;
        }

        if(container.empty()) {
            while(size != imageSize) {
                cout << ")";
                size *= 2;
            }
            cout << endl;
        } else if(size < get<2>(container.top())) {
            while(size != get<2>(container.top())) {
                cout << ")";
                size *= 2;
            } 
        }


    }





    return 0;
}
