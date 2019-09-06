#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <cstring>

#define MAX 20001

using namespace std;


int edges[MAX][MAX];
int nodeNum, edgeNum, start;



int main(void) {    
    cin >> nodeNum >> edgeNum >> start;

    memset(edges, 0, sizeof(edges));

    for(int i = 0; i < edgeNum; i++) {
        int from, to, weight;
    
        cin >> from >> to >> weight;

        edges[from][to] = weight;
    }

    // for(int i = 0; i < edges.size(); i++) {
    //     cout << i << ":" << endl;
    //     for(auto edge: edges[i]) {
    //         cout << edge.first << " " << edge.second << endl;
    //     }
    // }

    vector<int> costs = vector<int>(nodeNum + 1, -1);
    vector<bool> explored = vector<bool>(nodeNum + 1, false);

    auto loop = [&explored, &costs](int node) {
        explored[node] = true;
        int cost = costs[node];
        cost = cost == -1 ? 0 : cost;

        for(auto to: edges[node]) {
            // cout << "from: " << node << " to: " << to.first;
            int sum = edges[to] + cost;
            // cout << " sum: " << sum << endl;;
            if(costs[to.first] == -1 || costs[to.first] > sum) {
                // cout << "update: " << to.first << endl;
                costs[to.first] = sum;
            }
        }
    };


    loop(start);

    while(true) {
        int minNode = -1;
        for(int i = 1; i < explored.size(); i++) {
            if(explored[i] == false) {
                if(minNode == -1) {
                    minNode = i;
                } else if(costs[i] < costs[minNode]) {
                    minNode = i;
                }
            }
        }


        if(minNode == -1) { 
            costs[start] = 0;
            break;
        } else {
            // cout << "minnode: " << minNode << endl;
            loop(minNode);
        }
    }

    for(int i = 1; i < costs.size(); i++) {
        int c = costs[i];
        if(c == -1) {
            cout << "INF";
        } else {
            cout << c;
        }
        cout << endl;
    }


    return 0;
}