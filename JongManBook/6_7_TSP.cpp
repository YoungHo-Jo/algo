#include <iostream>
#include <vector>



using namespace std;

#define MAX 10
#define INF 1e9

int n; // the number of cities
double dist[MAX][MAX];

double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
  
  // base
  // 모든 도시를 지나감
  // 따라서 출발한 도시로 돌아가야함
  if(path.size() == n) {
    return currentLength + dist[path[0]][path.back()];
  } 

  double ret = INF;
  
  // 갈 수 있는 도시들에 대해
  for(int next = 0; next < n; next++) {

    if(visited[next]) continue;

    // 갈 수 있으면 일단 가본다
    int here = path.back();
    path.push_back(next);
    visited[next] = true;
  
    double cand = shortestPath(path, visited, currentLength + dist[here][next]);

    // 가봤을때랑 다른경우와 비교하여 작은 것을 취한다
    ret = min(ret, cand);
    visited[next] = false;

    path.pop_back();
  }

  return ret;
}

int main(void) {


  return 0;
}
