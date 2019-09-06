#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <string>


using namespace std;


vector<vector<pair<int, int> > > edges;
int nodeNum, edgeNum, start;
const char* ENDL = "\n";



int main(void) {    
    // ios::sync_with_stdio(false);

    cin >> nodeNum >> edgeNum >> start;

    edges = vector<vector<pair<int, int> > >(nodeNum + 1);

    for(int i = 0; i < edgeNum; i++) {
        int from, to, weight;
    
        cin >> from >> to >> weight;

        edges[from].push_back(make_pair(to, weight));
    }

    vector<int> costs = vector<int>(nodeNum + 1, -1);
    priority_queue<pair<int, int> > pq;

    auto loop = [&pq, &costs](int node) {
        int cost = costs[node];
        cost = cost == -1 ? 0 : cost;

        for(auto to: edges[node]) {
            int sum = to.second + cost;
            if(costs[to.first] == -1 || costs[to.first] > sum) {
                costs[to.first] = sum;
                pq.push(make_pair(to.first, costs[to.first]));
            }
        }
    };

    loop(start);

    while(true) {
        if(pq.empty() == false) {
            auto min = pq.top().first;
            pq.pop();
            loop(min);
        } else {
            costs[start] = 0;
            break;
        }
    }


    // cout spends more time
    string result = "";
    for(int i = 1; i < costs.size(); i++) {
        int c = costs[i];
        if(c == -1) {
            result += "INF";
            // cout << "INF";
        } else {
            result += to_string(c);
            // cout << c;
        }
        result += "\n";
        // cout << ENDL;
    }
    cout << result;


    return 0;
}