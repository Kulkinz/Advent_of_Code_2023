using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <numeric>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 9" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day9.txt)");
  string str;

  vector<vector<vector<long long>>> aaa;

  while (getline(file, str)) {
    vector<long long> data;
    cout << str << endl;
    vector<string> out;
    tokenize(str, ' ', out);
    for(auto &it : out) {
      data.push_back(stoll(it));
    }
    vector<vector<long long>> bbb;
    bbb.push_back(data);
    aaa.push_back(bbb);
  }

  for (auto &it : aaa) {
    vector<long long> curr = it[0];
    while (count(curr.begin(), curr.end(), 0) != curr.size()) {
      vector<long long> next;
      for (int i = 1; i < curr.size(); i++) {
        next.push_back(curr[i] - curr[i-1]);
      }
      it.push_back(next);
      curr = next;
    }
  }

  long long sum = 0;
  for (auto &it : aaa) {
    it[it.size() - 1].push_back(0);
    for (int i = (it.size() - 2); i >= 0; i--) {
      it[i].push_back(it[i].back() + it[i + 1].back());
    }
    sum += it[0].back();
  }

  cout << "Part 1: " << sum << endl;

  sum = 0;
  for (auto &it : aaa) {
    it[it.size() - 1].insert(it[it.size() - 1].begin(), 0);
    for (int i = (it.size() - 2); i >= 0; i--) {
      it[i].insert(it[i].begin(), it[i][0] - it[i + 1][0]);
    }
    sum += it[0][0];
  }

  cout << "Part 2: " << sum << endl;

  return 0;
}
