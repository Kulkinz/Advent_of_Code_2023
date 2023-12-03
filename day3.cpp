using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct part {
  string num;
  int posX;
  int posY;
};

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
  cout << "Day 3" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day3.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    cout << str << endl;
    data.push_back(str);
  }

  vector<part> parts;

  for (int y = 0; y < data.size(); ++y) {
    bool processing = false;
    part curr = {"",0,0};
    for (int x = 0; x < data[0].size(); ++x) {
      char n = data[y][x];
      if (!processing) {
        if (isdigit(n)) {
          processing = true;
          curr.num.push_back(n);
          curr.posX = x;
          curr.posY = y;
        }
      } else {
        if (isdigit(n)) {
          curr.num.push_back(n);
        } else {
          processing = false;
          parts.push_back(curr);
          curr = {"",0,0};
        }
      }
    }
    if (processing) {
      parts.push_back(curr);
    }
  }

  map<coord, vector<part>> gears;

  int sum = 0;
  for ( auto &it : parts ) {
    bool validPart = false;
    int xMin = max(0, it.posX - 1);
    int xMax = min(it.posX + (int) it.num.size(), (int) data[0].size() - 1);
    // check above
    if (it.posY - 1 >= 0) {
      for (int x = xMin; x <= xMax; ++x) {
        if (data[it.posY - 1][x] != '.') {
          if (data[it.posY - 1][x] == '*') {
            gears[{x, it.posY - 1}].push_back(it);
          }
          validPart = true;
        }
      }
    }
    // check middle
    if (it.posX - 1 >= 0) {
      if (data[it.posY][it.posX - 1] != '.') {
        if (data[it.posY][it.posX - 1] == '*') {
          gears[{it.posX - 1, it.posY}].push_back(it);
        }
        validPart = true;
      }
    }
    if (it.posX + it.num.size() <= data[0].size() - 1) {
      if (data[it.posY][it.posX + it.num.size()] != '.') {
        if (data[it.posY][it.posX + it.num.size()] == '*') {
          gears[{it.posX + (int) it.num.size(), it.posY}].push_back(it);
        }
        validPart = true;
      }
    }
    // check below
    if (it.posY + 1 <= data.size() - 1) {
      for (int x = xMin; x <= xMax; ++x) {
        if (data[it.posY + 1][x] != '.') {
          if (data[it.posY + 1][x] == '*') {
            gears[{x, it.posY + 1}].push_back(it);
          }
          validPart = true;
        }
      }
    }

    if (validPart) {
      sum += stoi(it.num);
    }
  }

  cout << "Part 1: " << sum << endl;

  int gearSum = 0;
  for (const auto & [key, value] : gears) {
    if (value.size() == 2) {
      int one = stoi(value[0].num);
      int two = stoi(value[1].num);
      gearSum += one * two;
    }
  }

  cout << "Part 2: " << gearSum << endl;


  return sum;
}