#include <iostream>
#include <vector>

#define N 0
#define S 1
#define CLOCK_WISE 1  
#define COUNT_CLOCK_WISE -1
#define GEAR_NUM 4
#define TOOTH_NUM 8
#define O_CLOCK 0
#define LEFT_SIDE 6
#define RIGHT_SIDE 2


using namespace std;

struct Operation {
    int whichGear;
    int direction;
    Operation(int _whichGear, int _direction) {
        whichGear = _whichGear;
        direction = _direction;
    }
};

void leftShift(vector<int>& v) {

    vector<int> temp = v;
    for(int i = 0; i < v.size() - 1; i++) {
        v[i] = temp[i + 1];
    }
    v[v.size() - 1] = temp.front(); 

}

void rightShift(vector<int>& v) {
    vector<int> temp = v;

    for(int i = 1; i < v.size(); i++) {
        v[i] = temp[i - 1];
    }
    v[0] = temp.back();
}

void doRotate(vector<int>& v, Operation oper) {
    if(oper.direction == CLOCK_WISE) {
        rightShift(v);
    } else if(oper.direction == COUNT_CLOCK_WISE) {
        leftShift(v);
    }
}

vector<vector<int> > gears;
vector<Operation> operations;

vector<vector<int> > getState() {
    vector<int> left, middle, right;
    left.push_back(gears[0][RIGHT_SIDE]);
    left.push_back(gears[1][LEFT_SIDE]);

    middle.push_back(gears[1][RIGHT_SIDE]);
    middle.push_back(gears[2][LEFT_SIDE]);

    right.push_back(gears[2][RIGHT_SIDE]);
    right.push_back(gears[3][LEFT_SIDE]);

    vector<vector<int> > state;
    state.push_back(left);
    state.push_back(middle);
    state.push_back(right);

    return state;
}

vector<int> getDirection(Operation oper) {
    vector<int> direction(4);

    int operDirection = oper.direction;

    if(oper.whichGear%2 == 0) {
        direction[0] = oper.direction;
        direction[1] = oper.direction * -1;
        direction[2] = oper.direction;
        direction[3] = oper.direction * -1;
    } else {
        direction[0] = oper.direction * -1;
        direction[1] = oper.direction;
        direction[2] = oper.direction * -1;
        direction[3] = oper.direction;
    }

    return direction;
}


const int SCORE[4][2] = {
    {0, 1},
    {0, 2},
    {0, 4},
    {0, 8}
};


void printGears() {
    for(auto gear = gears.begin(); gear != gears.end(); gear++) {
        for(auto tooth = gear->begin(); tooth != gear->end(); tooth++) {
            cout << *tooth;
        }
        cout << endl;
    }
}

int main(void) {
    // cout << "Enter Gaer states: " << endl;
    for(int i = 0; i < GEAR_NUM; i++) {
        vector<int> gear;
        string dirTemp;
        cin >> dirTemp;
        for(int j = 0; j < TOOTH_NUM; j++) {
            gear.push_back(dirTemp[j] - '0');
        }
        gears.push_back(gear);
    }
    // cout << "done" << endl;

    // printGears();
    

    // cout << "Enter the number of operations: " << endl;
    int opeartionNum;
    cin >> opeartionNum;
    // cout << "done" << endl;

    // cout << "Enter Operations: " << endl;
    for(int i = 0; i < opeartionNum; i++) {
        int whichGear, direction;
        cin >> whichGear >> direction;
        operations.push_back(Operation(whichGear - 1, direction));
    }
    // cout << "done" << endl;

    for(auto oper = operations.begin(); oper != operations.end(); oper++) {
        // cout << "round: " << (oper - operations.begin()) << endl;
        auto preState = getState();
        doRotate(gears[oper->whichGear], *oper);
        auto currentState = getState();

        vector<bool> done(GEAR_NUM, false);
        vector<bool> rotated(GEAR_NUM, false);
        done[oper->whichGear] = true;
        rotated[oper->whichGear] = true; 

        while(true) {
            for(int i = 0; i < preState.size(); i++) {
                if(done[i] != done[i + 1]) {
                    if(preState[i][0] == preState[i][1]) {
                        // cout << "No Rotate " << i << " " << i + 1 << endl;
                    } else {
                        auto direction = getDirection(*oper);
                        if(!done[i] && rotated[i + 1]) {
                            // cout << "Rotate " << i << endl;
                            doRotate(gears[i], Operation(i, direction[i]));
                            rotated[i] = true;
                        } else if(!done[i + 1] && rotated[i]) {
                            // cout << "Rotate " << i + 1 << endl;
                            doRotate(gears[i + 1], Operation(i + 1, direction[i + 1]));
                            rotated[i + 1] = true;
                        }
                    }
                    done[i] = true;
                    done[i + 1] = true;
                }
            }

            preState = currentState;
            currentState = getState();

            bool isTheEnd = true;
            for(int i = 0; i < GEAR_NUM; i++) {
                if(done[i] == false) {
                    isTheEnd = false;
                    break;
                }
            }

            if(isTheEnd) {
                break;
            }
        }
        // printGears();
    }




    int score = 0;
    for(int i = 0; i < gears.size(); i++) {
        score += SCORE[i][gears[i][O_CLOCK]];
    }


    
    cout << score << endl;


    return 0;
}


