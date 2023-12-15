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
  cout << "Day 11" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day11.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    cout << str << endl;
    vector<string> out;
    data.push_back(str);
  }

  map<int, long long int> xExpansion;
  map<int, long long int> yExpansion;
  int expansionFactor = 1000000;

  xExpansion[0] = 0;
  yExpansion[0] = 0;

  for (int i = 1; i < data.size(); i++) { // y
    if (!data[i].contains('#')) {
      yExpansion[i] = yExpansion[i - 1] + expansionFactor;
    } else {
      yExpansion[i] = yExpansion[i - 1] + 1;
    }
  }

  vector<int> spots;
  for (int x = 1; x < data[0].size(); x++) {
    bool contains = false;
    for (int y = 0; y < data.size(); y++) {
      if (data[y][x] == '#') {
        contains = true;
        break;
      }
    }
    if (!contains) {
      xExpansion[x] = xExpansion[x - 1] + expansionFactor;
    } else {
      xExpansion[x] = xExpansion[x - 1] + 1;
    }
  }

  vector<coord> galaxies;
  for (int y = 0; y < data.size(); y++) {
    for (int x = 0; x < data[0].size(); x++) {
      if (data[y][x] == '#') {
        galaxies.push_back({x,y});
      }
    }
  }

  long long int sum = 0;
  for (int i = 0; i < galaxies.size() - 1; i++) {
    for (int j = i + 1; j < galaxies.size(); j++) {
      sum += abs(xExpansion[galaxies[i].x] - xExpansion[galaxies[j].x]) + abs(yExpansion[galaxies[i].y] - yExpansion[galaxies[j].y]);
    }
  }

  cout << "Part 1: " << sum << endl;


  return 0;
}
