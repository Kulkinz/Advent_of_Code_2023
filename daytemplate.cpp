using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

int main() {
  cout << "Day 1" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day1.txt)");
  string str;

  while (getline(file, str)) {
    cout << str << endl;
  }

  return 0;
}