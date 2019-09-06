#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

struct Point {
	int x;
	int y;
	Point(int _x, int _y): x(_x), y(_y) {};
};

int pointsNum, canFillNum;

vector < Point > points;

int main(void) {
	ios::sync_with_stdio(false);

	Point start(0, 0), goal(10000, 10000);

	cin >> pointsNum >> canFillNum;

	points.push_back(start);
	for (int i = 0; i < pointsNum; i++) {
		int x, y;
		cin >> x >> y;

		points.emplace_back(x, y);
	}
	points.push_back(goal);


	auto getDistance = [ & ](const Point & lhs,
		const Point & rhs) {
		return sqrt(pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2));
	};

	auto getRequireFuel = [ & ](const Point & lhs,
		const Point & rhs) {
		int d = (int) getDistance(lhs, rhs);
		int require = d / 10;
		if (d % 10 != 0) {
			require++;
		}

		return require;
	};


	// sort(points.begin(), points.end(), [&](const Point& lhs, const Point& rhs) {
	//     return getDistance(start, lhs) < getDistance(start, rhs); 
	// });

	// auto findMin = [&](int from, int to) {
	//     int index = 0; 
	//     int min = INT32_MAX;
	//     for(int i = from; i <= to; i++) {
	//         auto p = points[i];
	//         int m = max(getRequireFuel(points[from], p), getRequireFuel(p, points[to]));
	//         if(m < min) {
	//             index = i;
	//             min = m;
	//         }
	//     }
	//     return make_pair(index, min);
	// };

	// auto findTwoPoint = [&](int from, int to) {
	//     auto p = findMin(from, to);

	//     auto lhs = findMin(from, p.first);
	//     auto rhs = findMin(lhs.first, to);
	//     return max(lhs.second, rhs.second);
	// };

	// priority_queue<int> pq;
	// stack<pair<pair<int, int>, int> > s;

	// s.push(make_pair(make_pair(0, points.size() - 1), canFillNum));

	// while(s.empty() == false) {
	//     auto fromTo = s.top().first; 
	//     auto canFillFuelNum = s.top().second;
	//     s.pop();

	//     if(canFillFuelNum == 0) {
	//         cout << "End" << endl;
	//         break;
	//     } else if(canFillFuelNum == 1) {
	//         cout << "one" << endl;
	//         auto pair = findMin(fromTo.first, fromTo.second);
	//         pq.push(pair.second);
	//         continue;
	//     } else if(canFillFuelNum == 2) {
	//         cout << "two" << endl;
	//         auto fuel = findTwoPoint(fromTo.first, fromTo.second);             
	//         pq.push(fuel);
	//         continue;
	//     } else if(canFillFuelNum%2 == 0) {
	//         cout << "Even" << endl;
	//         auto middlePoint = findMin(fromTo.first, fromTo.second);
	//         s.push(make_pair(make_pair(fromTo.first, middlePoint.first), canFillFuelNum/2));
	//         s.push(make_pair(make_pair(middlePoint.first, fromTo.second), canFillFuelNum/2));
	//     } else {
	//         cout << "Odd" << endl;
	//         auto middlePoint = findMin(fromTo.first, fromTo.second);
	//         s.push(make_pair(make_pair(fromTo.first, middlePoint.first), (canFillFuelNum - 1)/2));
	//         s.push(make_pair(make_pair(fromTo.first, middlePoint.first), (canFillFuelNum - 1)/2));
	//     }
	// }
	// 
	// cout << pq.top() << endl;

	auto bfs = [ & ](int givenFuel) {
		queue<pair<int, int>> q; // where, lending count
		bool visited[10000 + 2];
		memset(visited, false, sizeof(visited));

		q.push(make_pair(0, 0));
		visited[0] = true;

		bool ret = false;
		while (q.empty() == false) {
			auto where = q.front().first;
			auto count = q.front().second;
			q.pop();

			// cout << "where: " << where << " points Size: " << points.size() - 1 << endl;
			if (where == points.size() - 1) {
				// cout << "count: " << count << " canfill: " << canFillNum + 1 << endl;
				if (count <= canFillNum + 1) {
					ret = true;	
					break;
				} else {
					ret = false;
					continue;
				}
			}

			for (int i = 0; i < points.size(); i++) {
				if (visited[i] == true) {
					continue;
				}

				if (getRequireFuel(points[where], points[i]) <= givenFuel) {
					// cout << "Push " << i << " count: " << count + 1 << endl;
					visited[i] = true;
					q.push(make_pair(i, count + 1));
				}
			}
		}
		return ret;
	};

	int lhs = 1;
	int rhs = getRequireFuel(points.front(), points.back());

	while (lhs <= rhs) {
		int mid = (lhs + rhs)/2;
		// cout << mid << endl;
		// cout << "lhs: " << lhs << " rhs: " << rhs << " mid: " << mid << endl;

		if (bfs(mid) == true) {
			// cout << "true" << endl;
			rhs = mid - 1;
		} else {
			// cout << "false" << endl;
			lhs = mid + 1;
		}
	}

	cout << lhs << endl;

	return 0;
}