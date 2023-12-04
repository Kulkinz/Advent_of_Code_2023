using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 4" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day4.txt)");
  string str;

  vector<string> cards;
  map<int, int> winnings;

  int x = 1;
  while (getline(file, str)) {
    cout << str << endl;
    cards.push_back(str);
    winnings[x] = 1;
    x++;
  }

  int sum = 0;
  int instances = 0;
  x = 1;
  for (auto &card : cards) {

    vector<string> out;
    tokenize(card, ' ', out);

    vector<int> nums;
    vector<int> winning;
    int i = 2;
    while (out[i] != "|") {
      nums.push_back(stoi(out[i]));
      i++;
    }
    i++;
    while (i < out.size()) {
      winning.push_back(stoi(out[i]));
      i++;
    }

    int total = 0;
    for (auto &num : nums) {
      if (std::find(winning.begin(), winning.end(), num) != winning.end()) {
        total++;
      }
    }
    if (total > 0) {
      sum += pow(2, total-1);
    }
    for (int j = x+1; j <= x+total; j++) {
      winnings[j] += winnings[x];
    }
    instances += winnings[x];
    x++;
  }

  cout << "Part 1: " << sum << endl;
  cout << "Part 2: " << instances << endl;

  return sum;
}