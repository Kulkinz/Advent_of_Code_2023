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

struct picross {
  string springs;
  vector<int> counts;
};

struct combo {
  string spring;
  int positionChecking;
  int count;
};

int main() {
  cout << "Day 12" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day12.txt)");
  string str;

  vector<picross> data;

  while (getline(file, str)) {
    cout << str << endl;
    vector<string> out;
    tokenize(str, ' ', out);
    vector<int> nums;
    vector<string> out1;
    tokenize(out[1], ',', out1);
    for (auto &it : out1) {
      nums.push_back(stoi(it));
    }
    for (auto &it : out1) { // part 2
      nums.push_back(stoi(it));
    }
    for (auto &it : out1) {
      nums.push_back(stoi(it));
    }
    for (auto &it : out1) {
      nums.push_back(stoi(it));
    }
    for (auto &it : out1) {
      nums.push_back(stoi(it));
    }
    string aaa = out[0];
    aaa.push_back('?');
    aaa += out[0];
    aaa.push_back('?');
    aaa += out[0];
    aaa.push_back('?');
    aaa += out[0];
    aaa.push_back('?');
    aaa += out[0];
    data.push_back({aaa, nums});
  }

  long long sum = 0;
  int n = 0;
  for (auto &puzzle : data) {
    n++;
    vector<combo> curr;
    curr.push_back({puzzle.springs, 0, 0});
    for (int i = 0; i < puzzle.springs.size(); i++) {
      vector<combo> next;
      for (auto it : curr) {
        if (it.spring[i] == '?') {
          bool validity = true;
          int oldCount = it.count;
          int oldPositionChecking = it.positionChecking;
          it.spring[i] = '.';
          if (it.count > 0) {
            if (it.count != puzzle.counts[it.positionChecking]) {
              validity = false;
            } else {
              it.positionChecking++;
              it.count = 0;
            }
          }
          if (validity) {
            next.push_back({it.spring, it.positionChecking, it.count});
          }

          it.positionChecking = oldPositionChecking;
          it.count = oldCount;
          validity = true;
          it.spring[i] = '#';
          if (it.positionChecking >= puzzle.counts.size()) {
            validity = false;
          } else {
            it.count++;
          }
          if (validity) {
            next.push_back({it.spring, it.positionChecking, it.count});
          }
        } else { // may eliminate
          if (it.count > 0 && it.spring[i] == '.') {
            if (it.count != puzzle.counts[it.positionChecking]) {
              continue;
            }
            it.positionChecking++;
            it.count = 0;
          } else if (it.spring[i] == '#') {
            if (it.positionChecking >= puzzle.counts.size()) {
              continue;
            }
            it.count++;
          }
          next.push_back(it);
        }
      }

      curr.clear();
      curr = next;
    }
    vector<string> valid;
    for (auto &permutation : curr) {
      bool validity = true;
      if (permutation.count > 0) {
        if (permutation.count != puzzle.counts[permutation.positionChecking]) {
          validity = false;
        }
        permutation.positionChecking++;
      }
      if (permutation.positionChecking != puzzle.counts.size()) {
        validity = false;
      }
      if (validity) {
        valid.push_back(permutation.spring);
      }
    }
    sum += valid.size();
    cout << n << ": " << valid.size() << endl;
  }

  cout << sum << endl;

  return 0;
}
