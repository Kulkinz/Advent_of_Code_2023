using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <numeric>
#include "Helpers/HelperFunctions.h"

struct fork {
  string left;
  string right;
};

bool endState(vector<string> &currs) {
  for (auto &it : currs) {
    if (it[2] != 'Z') {
      return false;
    }
  }
  return true;
}

int main() {
  cout << "Day 8" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day8.txt)");
  string str;

  string path;
  map<string, fork> network;

  bool space = false;

  while (getline(file, str)) {
    cout << str << endl;
    if (str == "") {
      space = true;
      continue;
    }
    if (space) {
      vector<string> out;
      tokenize(str, ' ', out);

      string node = out[0];
      string left = out[2].substr(1, 3);
      string right = out[3].substr(0, 3);
      network[node] = {left, right};
    } else {
      path = str;
    }
  }

  string curr = "AAA";
  int cum = 0;
  int i = 0;
  while (curr != "ZZZ") {
    char spot = path[i % path.size()];
    if (spot == 'R') {
      curr = network[curr].right;
    } else {
      curr = network[curr].left;
    }
    cum++;
    i++;
  }

  cout << "Part 1: " << cum << endl;

  vector<string> currents;
  for (const auto &[key, value] : network) {
    if (key[2] == 'A') {
      currents.push_back(key);
    }
  }

  vector<int> loop;
  for (auto &it : currents) {
    int cum = 0;
    while (it[2] != 'Z') {
      char spot = path[cum % path.size()];
      if (spot == 'R') {
        it = network[it].right;
      } else {
        it = network[it].left;
      }
      cum++;
    }
    loop.push_back(cum);
  }

  long long ans = loop[0];
  for (int i = 1; i < loop.size(); i++) {
    ans = lcm(ans, loop[i]);
  }

  cout << "Part 2: " << ans << endl;

  return 0;
}
