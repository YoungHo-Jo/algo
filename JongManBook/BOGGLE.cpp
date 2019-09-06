#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

#ifdef DEBUG
#define D(s) cout << " [DEBUG] " << __FUNCTION__ << " " << __LINE__ << " >> " << s
#else
#define D(s)
#endif

#define endl '\n'
#define MAX 5

char board[MAX][MAX];

const int dx[8] = {
  -1, -1, -1, 1,
  1, 1, 0, 0
};

const int dy[8] = {
  -1, 0, 1, -1,
  0, 1, -1, 1
};

bool inRange(int y, int x)
{
  D("Check range: " << y << " " << x << endl);
  return 0 <= y && y < MAX && 0 <= x && x < MAX;
}

bool hasWord(int y, int x, const string &word)
{
  D("has word " << y << " " << x << " " << word << endl);
  if (!inRange(y, x))
    return false; // base
  D("is match" << endl);
  if (board[y][x] != word[0])
    return false; // base
  D("is size == 1" << endl);
  if (word.size() == 1)
    return true; // base

  D("Check around the char" << endl);
  for (int direction = 0; direction < 8; direction++)
  {
    int nextY = y + dy[direction], nextX = x + dx[direction];

    if (hasWord(nextY, nextX, word.substr(1)))
      return true;
  }

  return false;
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  char c;
  D("Get board" << endl);
  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      cin >> c;
      board[i][j] = c;
    }
  }

  string wordToFind;
  cin >> wordToFind;

  bool found = false;

  D("Check in the board" << endl);
  for (int y = 0; y < MAX; y++)
  {
    for (int x = 0; x < MAX; x++)
    {
      D("where " << y << " " << x << endl);
      if (hasWord(y, x, wordToFind))
      {
        found = true;
        break;
      }
    }
  }

  cout << (found ? "has it" : "no") << endl;

  return 0;
}
