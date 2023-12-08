using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "Helpers/HelperFunctions.h"


int main() {
  cout << "Day 6" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day6.txt)");
  string str;

  vector<string> data;
  // 0 - time
  // 1 - distance

  while (getline(file, str)) {
    cout << str << endl;
    data.push_back(str);
  }

  vector<int> times;
  vector<int> distances;
  string timesCombined;
  string distancesCombined;

  vector<string> out;
  tokenize(data[0], ' ', out);
  for (int i = 1; i < out.size(); i++) {
    times.push_back(stoi(out[i]));
    timesCombined.append(out[i]);
  }
  out.clear();
  tokenize(data[1], ' ', out);
  for (int i = 1; i < out.size(); i++) {
    distances.push_back(stoi(out[i]));
    distancesCombined.append(out[i]);
  }

  long long sum = 1;
  for (int i = 0; i < times.size(); i++) {
    int options = 0;
    for (int n = 1; n < times[i]; n++) {
      int distancePer = (times[i] - n) * n;
      if (distancePer > distances[i]) {
        options++;
      }
    }
    sum *= options;
  }

  cout << "Part 1: " << sum << endl;

  long long timesSum = stoll(timesCombined);
  long long distancesSum = stoll(distancesCombined);

  int options = 0;
  for (long long n = 1; n < timesSum; n++) {
    long long distancePer = (timesSum - n) * n;
    if (distancePer > distancesSum) {
      options++;
    }
  }

  cout << "Part 2: " << options << endl;

  return 0;
}
