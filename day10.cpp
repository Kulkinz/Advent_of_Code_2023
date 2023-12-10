using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <numeric>
#include <queue>
#include "Helpers/HelperFunctions.h"

struct coord {
  int x;
  int y;

  bool operator=(const coord &o) const {
    return x == o.x && y == o.y;
  }

  bool operator<(const coord &o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
};

bool operator==(const coord& lhs, const coord& rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}

coord operator-(const coord& lhs, const coord& rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

ostream& operator<<(ostream& os, const coord &o) {
  return os << o.x << "," << o.y;
}

int main() {
  cout << "Day 10" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day10.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    cout << str << endl;
    vector<string> out;
    data.push_back(str);
  }

  map<coord, set<coord>> pipes;

  coord start;

  for (int y = 0; y < data.size(); y++) {
    for (int x = 0; x < data[0].size(); x++) {
      char node = data[y][x];
      char connect;
      switch (node) {
        case '|': // north south
          if (y - 1 < 0) continue;
          connect = data[y - 1][x];
          if (connect == '|' || connect == '7' || connect == 'F' || connect == 'S') {
            pipes[{x,y}].insert({x,y - 1}); // north
            pipes[{x,y - 1}].insert({x,y});
          }

          if (y + 1 >= data.size()) continue;
          connect = data[y + 1][x];
          if (connect == '|' || connect == 'L' || connect == 'J' || connect == 'S') {
            pipes[{x,y}].insert({x,y + 1}); // south
            pipes[{x,y + 1}].insert({x,y});
          }
          break;
        case '-': // east west
          if (x + 1 >= data[0].size()) continue;
          connect = data[y][x + 1];
          if (connect == '-' || connect == 'J' || connect == '7' || connect == 'S') {
            pipes[{x, y}].insert({x + 1, y}); // east
            pipes[{x + 1, y}].insert({x, y});
          }

          if (x - 1 < 0) continue;
          connect = data[y][x - 1];
          if (connect == '-' || connect == 'L' || connect == 'F' || connect == 'S') {
            pipes[{x, y}].insert({x - 1, y}); // west
            pipes[{x - 1, y}].insert({x, y});
          }
          break;
        case 'L': // north east
          if (y - 1 < 0) continue;
          connect = data[y - 1][x];
          if (connect == '|' || connect == '7' || connect == 'F' || connect == 'S') {
            pipes[{x,y}].insert({x,y - 1}); // north
            pipes[{x,y - 1}].insert({x,y});
          }

          if (x + 1 >= data[0].size()) continue;
          connect = data[y][x + 1];
          if (connect == '-' || connect == 'J' || connect == '7' || connect == 'S') {
            pipes[{x, y}].insert({x + 1, y}); // east
            pipes[{x + 1, y}].insert({x, y});
          }
          break;
        case 'J': // north west
          if (y - 1 < 0) continue;
          connect = data[y - 1][x];
          if (connect == '|' || connect == '7' || connect == 'F' || connect == 'S') {
            pipes[{x,y}].insert({x,y - 1}); // north
            pipes[{x,y - 1}].insert({x,y});
          }

          if (x - 1 < 0) continue;
          connect = data[y][x - 1];
          if (connect == '-' || connect == 'L' || connect == 'F' || connect == 'S') {
            pipes[{x, y}].insert({x - 1, y}); // west
            pipes[{x - 1, y}].insert({x, y});
          }
          break;
        case '7': // south west
          if (y + 1 >= data.size()) continue;
          connect = data[y + 1][x];
          if (connect == '|' || connect == 'L' || connect == 'J' || connect == 'S') {
            pipes[{x,y}].insert({x,y + 1}); // south
            pipes[{x,y + 1}].insert({x,y});
          }

          if (x - 1 < 0) continue;
          connect = data[y][x - 1];
          if (connect == '-' || connect == 'L' || connect == 'F' || connect == 'S') {
            pipes[{x, y}].insert({x - 1, y}); // west
            pipes[{x - 1, y}].insert({x, y});
          }
          break;
        case 'F': // south east
          if (y + 1 >= data.size()) continue;
          connect = data[y + 1][x];
          if (connect == '|' || connect == 'L' || connect == 'J' || connect == 'S') {
            pipes[{x,y}].insert({x,y + 1}); // south
            pipes[{x,y + 1}].insert({x,y});
          }

          if (x + 1 >= data[0].size()) continue;
          connect = data[y][x + 1];
          if (connect == '-' || connect == 'J' || connect == '7' || connect == 'S') {
            pipes[{x, y}].insert({x + 1, y}); // east
            pipes[{x + 1, y}].insert({x, y});
          }
          break;
        case 'S': // animal start
          start.x = x;
          start.y = y;
          break;
        default: // no pipe
          break;
      }
    }
  }

  set<coord> traversed;
  queue<coord> traversal;
  map<coord, int> count;

  traversal.push(start);

  while (!traversal.empty()) {
    coord popped = traversal.front();
    traversal.pop();
    traversed.insert(popped);
    for (auto &it : pipes[popped]) {
      if (!traversed.contains(it)) {
        traversal.push(it);
        count[it] = count[popped] + 1;
      }
    }
  }

  int ans = 0;
  for (const auto & [key, value] : count) {
    ans = max(ans, value);
  }

  cout << "Part 1: " << ans << endl;

  map<coord, bool> grid;

  int turnCount = 0; // + is right (ccw), - is left (cw)
  coord curr = start;
  coord last = *pipes[start].begin();
  coord initialLast = last;
  do {
    grid[curr] = true;
    coord next = {0, 0};
    for (auto &it : pipes[curr]) {
      if (it != last) {
        next.x = it.x;
        next.y = it.y;
      }
    }
    if (next.x != last.x && next.y != last.y) {
      coord change1 = curr - last;
      coord change2 = next - curr;
      if (change1.x == 1) { // ->
        if (change2.y == 1) { // \/
          turnCount++;
        } else if (change2.y == -1) { // ^
          turnCount--;
        }
      } else if (change1.x == -1) { // <-
        if (change2.y == 1) { // \/
          turnCount--;
        } else if (change2.y == -1) { // ^
          turnCount++;
        }
      } else if (change1.y == 1) { // \/
        if (change2.x == 1) { // ->
          turnCount--;
        } else if (change2.x == -1) { // <-
          turnCount++;
        }
      } else if (change1.y == -1) { // ^
        if (change2.x == 1) { // ->
          turnCount++;
        } else if (change2.x == -1) { // <-
          turnCount--;
        }
      }
    }

    last.x = curr.x;
    last.y = curr.y;
    curr.x = next.x;
    curr.y = next.y;

  } while (curr != start);

  for (int y = 0; y < data.size(); y++) {
    for (int x = 0; x < data[0].size(); x++) {
      if (grid[{x,y}]) {
        cout << data[y][x];
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }

  cout << "Turn Count: " << turnCount << endl;
  vector<coord> inside;
  int modifier = 0;
  if (turnCount > 0) { // to the right of the line
    modifier = 1;
  } else { // to the left of the line
    modifier = -1;
  }

  curr = start;
  last = initialLast;
  do {
    coord next = {0, 0};
    for (auto &it : pipes[curr]) {
      if (it != last) {
        next.x = it.x;
        next.y = it.y;
      }
    }
    coord direction = next - curr;
    coord side = curr;
    if (direction.x == 1) { // ->
      side.y += modifier;
    } else if (direction.x == -1) { // <-
      side.y -= modifier;
    } else if (direction.y == -1) { // ^
      side.x += modifier;
    } else if (direction.y == 1) { // \/
      side.x -= modifier;
    }

    if (!grid[side]) {
      inside.push_back(side);
    }
    side.x += direction.x;
    side.y += direction.y;
    if (!grid[side]) {
      inside.push_back(side);
    }

    last.x = curr.x;
    last.y = curr.y;
    curr.x = next.x;
    curr.y = next.y;

  } while (curr != start);

  set<coord> traversalFill;
  queue<coord> traversalFillQueue;

  for (auto &it : inside) {
    traversalFillQueue.push(it);
  }

  while (!traversalFillQueue.empty()) {
    coord popped = traversalFillQueue.front();
    traversalFillQueue.pop();
    traversalFill.insert(popped);

    coord up = {popped.x, popped.y - 1};
    coord down = {popped.x, popped.y + 1};
    coord left = {popped.x - 1, popped.y};
    coord right = {popped.x + 1, popped.y};

    if (!grid[up] && !traversalFill.contains(up)) {
      traversalFillQueue.push(up);
    }
    if (!grid[down] && !traversalFill.contains(down)) {
      traversalFillQueue.push(down);
    }
    if (!grid[left] && !traversalFill.contains(left)) {
      traversalFillQueue.push(left);
    }
    if (!grid[right] && !traversalFill.contains(right)) {
      traversalFillQueue.push(right);
    }
  }

  cout << "Part 2: " << traversalFill.size() << endl;

  return 0;
}
