#include <iostream>
#include <vector>


using namespace std;

const int coverType[4][3][2] = {
    {
        {0, 0},
        {1, 0},
        {0, 1}
    },
    {
        {0, 0},
        {0, 1},
        {1, 1}
    },
    {
        {0, 0},
        {1, 0},
        {1, 1}
    },
    {
        {0, 0},
        {1, 0},
        {1, -1}
    }
};

bool set(vector<vector<int> >& board, int y, int x, int type, int delta) {
    bool ok = true;

    for(int i = 0; i < 3; i++) {
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board.size()) {
            ok = false;
        } else if((board[ny][nx] += delta) > 1) {
            ok = false; 
        }
    }

    return ok;
}

int cover(vector<vector<int> >& board) {
    int y = -1, x = -1;
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[i].size(); j++) {
            if(board[i][j] == 0) {
                y = i;
                x = j;
                break;
            }
        }

        if(y != -1) break;
    }

    if(y == -1) return 1;
    int ret = 0;
    for(int type = 0; type < 4; type++) {
        if(set(board, y, x, type, 1)) {
            ret += cover(board);
        }
        set(board, y, x, type, -1);
    }
    

    return ret;
}


int main(void) {
    int testCaseNum;
    cin >> testCaseNum;

    for(int i = 0; i < testCaseNum; i++) {
        int height, width;
        cin >> height >> width;

        vector<vector<int> > board;
        string line;
        for(int lineNum = 0; lineNum < height; lineNum++) {
            cin >> line; 
            vector<int> v;
            
            for(int eleNum = 0; eleNum < width; eleNum++) {
                if(line[eleNum] == '#') {
                    v.push_back(1);
                } else if(line[eleNum] == '.') {
                    v.push_back(0);
                }
            }
            board.push_back(v);
        }
        int ret = cover(board);
        cout << ret << endl;
    }


    return 0;
}

