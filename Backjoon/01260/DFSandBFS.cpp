#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
            
#define N_MAX 1000
#define E_MAX 10000

using namespace std;

struct Node {
    int from;
    int to;
    Node(int f, int t): from(f), to(t) {};
};

bool nodes[N_MAX + 1][E_MAX + 1];
int nodeNum, edgeNum, start;
void dfs();
void bfs();

auto print = [](int n, bool space){
    cout << n << (space ? " " : "");
};


int main(void) {
    cin >> nodeNum;
    cin >> edgeNum;
    cin >> start;

    memset(nodes, false, sizeof(nodes));

    for(int i = 0; i < edgeNum; i++) {
        int from, to;
        cin >> from >> to;

        nodes[from][to] = true;
        nodes[to][from] = true;
    }

    dfs();
    bfs();    


    return 0;
}

void dfs() {
    stack<int> container;
    bool explored[N_MAX + 1];

    memset(explored, false, sizeof(explored));

    container.push(start);

    while(container.empty() == false) {
        int current = container.top();
        
        if(explored[current] == false) {
            cout << current << " ";
            explored[current] = true;
        }

        // cout << "pop: " << current << endl;
        container.pop();

        for(int i = N_MAX; i >= 0; i--) {
            if(nodes[current][i] == true
                && explored[i] == false) {
                    // cout << "push: " << i << endl;
                    container.push(i);
            } 
        } 
    }
    cout << endl;
    
}

void bfs() { 
    queue<int> container;
    bool explored[N_MAX + 1];

    memset(explored, false, sizeof(explored));

    container.push(start);

    while(container.empty() == false) {
        int top = container.front();

        if(explored[top] == false) {
            cout << top << " ";
            explored[top] = true;
        }
        // cout << "pop: " << top << endl;
        container.pop();

        for(int i = 1; i <= N_MAX; i++) {
            if(explored[i] == false 
                && nodes[top][i] == true) {
                
                // cout << "push: " << i << endl;
                container.push(i);
            }
        }

    }
    cout << endl;
    


}