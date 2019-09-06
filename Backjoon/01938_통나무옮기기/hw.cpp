#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int N;
bool isMove = false;

struct con{
    int r;
    int c;
    int ct;
    bool chk;
    //true -> vertical
    //false -> hortizental
};

struct visit{
    bool visit;
    bool direct;
};

int rl[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int ud[8] = {1, -1, 0, 0, 1, -1, 1, -1};

vector<vector<int>> mat;
vector<vector<visit>> visited;

int main(){
    ios::sync_with_stdio(false);
    cin >> N;
    mat.resize(N + 2, vector<int>(N + 2, 1));
    visited.resize(N + 2, vector<visit>(N + 2, {false, false}));

    vector<con> B;
    vector<con> E;

    string in;

    for (int i = 1; i <= N; i++){
        cout << "fuck    "<< i << endl;
        cin >> in;
        cout << "- 1\n";
        for (int j = 0; j < in.length(); j++){
            // cout << in[j] << " ";
            // if (in[j] == '1'){
            //     mat[i][j + 1] = 1;
            //     cout << "- 2\n";
            // }
            // else if (in[j] == 'B'){
            //     mat[i][j + 1] = 0;
            //     B.push_back({i, j + 1, 0, false});
            //     cout << "- 4\n";
            // }
            // else if (in[j] == 'E'){
            //     mat[i][j + 1] = 0;
            //     E.push_back({i, j + 1, 0, false});
            //     cout << "- 5\n";
            // }
            // else{
            //     mat[i][j + 1] = 0;
            //     cout << "- 3\n";
            // }
            // cout << in.size() << endl;
        }
    }

    cout <<" HELLO \n";

    queue<con> q;

    if(E[1].c + 1 == E[2].c) E[1].chk = false;
    else E[1].chk = true;

    if(B[1].c + 1 == B[2].c) q.push(B[1]);
    else q.push({B[1].r, B[1].c, 0, true});
    visited[B[1].r][B[1].c] = {true, B[1].chk};

    while(q.size()){
        int row = q.front().r;
        int col = q.front().c;
        int cnt = q.front().ct;
        bool chk = q.front().chk;

        if(row == E[1].r && col == E[1].c && E[1].chk == chk) {
            cout << cnt;
            isMove = true;
            break;
        }

        bool isTree = false;
        for(int i = 0; i < 8; i++) {
            if(mat[row + ud[i]][col + rl[i]] == 1) {
                isTree = true;
                break;
            }
        }

        if(!isTree) q.push({row, col, cnt, !chk});

        for(int i = 0; i < 4; i++){
            int _row = row + ud[i];
            int _col = col + rl[i];
            if(chk){
                if(_row + 2 == 1 || _row - 2 == 1) continue;
                else if(visited[_row][_col].visit && visited[_row][_col].direct == chk)
                    continue;
                else {
                    q.push({_row, _col, cnt + 1, chk});
                    visited[_row][_col].visit = true;
                    visited[_row][_col].direct = chk;
                }
            }
            else{
                if(_col + 2 == 1 || _col - 2 == 1) continue;
                else if(visited[_row][_col].visit && visited[_row][_col].direct == chk)
                    continue;
                else {
                    q.push({_row, _col, cnt + 1, chk});
                    visited[_row][_col].visit = true;
                    visited[_row][_col].direct = chk;
                }    
            }
        }
        q.pop();
    }

    if(!isMove) cout << 0;

    return 0;
}