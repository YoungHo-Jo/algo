#include <string>
#include <vector>

using namespace std;

const string days[7] = {
  "THU", "FRI", "SAT", "SUN", "MON", "TUE", "WED"
};

const int daysOfMonth[13] = {
  0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

string solution(int a, int b) {
    string answer = "";

    int daysFromStart = 0;
    for(int i = 1; i < a; i++) {
      daysFromStart += daysOfMonth[i];
    }
    daysFromStart += b;

    answer = days[daysFromStart % 7];

    return answer;
}