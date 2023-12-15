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

int main() {
  cout << "Day 13" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day13.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    cout << str << endl;
    vector<string> out;
    data.push_back(str);
  }

  return 0;
}
