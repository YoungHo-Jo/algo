#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> pi;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;



    queue<pi> bridge;
    ui enoughtWeight = weight;
    ui cnt = 0;

    while(true) {
      cnt++;
      D(cout << "Time: " << cnt << endl;)
      if(!bridge.empty() && cnt - bridge.front().second == bridge_length) {
        enoughtWeight += bridge.front().first;
        D(cout << "Bye truck: " << bridge.front().first << " when came: " << bridge.front().second << endl;)
        bridge.pop();

        if(truck_weights.size() == 0 && bridge.empty()) {
          break;
        }
      }

      auto front = truck_weights.front();
      if(front <= enoughtWeight && truck_weights.size() > 0) {
        D(cout << "Enought weight from: " << enoughtWeight;)
        enoughtWeight -= front;
        D(cout << " to: " << enoughtWeight << endl;)
        bridge.push(pi(front, cnt));
        truck_weights.erase(truck_weights.begin());

        D(
          cout << "Left trucks: " << endl; 
          for(auto t: truck_weights) {
            cout << t << " ";
          } 
          cout << endl;
        )
      }

    } 

    answer = cnt;    
    
    return answer;
}