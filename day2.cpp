using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 2" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day2.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    cout << str << endl;
    data.push_back(str);
  }
  // 12 red 13 green 14 blue

  int sum = 0;
  for(auto &str : data) {

    vector<string> out;
    tokenize(str, ' ', out);

    string val = out[1];
    val.pop_back();
    int game = stoi(val);

    int red = 0;
    int green = 0;
    int blue = 0;
    for (int i = 2; i < out.size(); i+=2) {
      string colour = out[i+1];
      int num = stoi(out[i]);
      if (colour.find("red") != std::string::npos) {
        red = max(red, num);
      } else if (colour.find("green") != std::string::npos) {
        green = max(green, num);
      } else if (colour.find("blue") != std::string::npos) {
        blue = max(blue, num);
      }
    }
    sum += (red * green * blue);
  }

  cout << sum << endl;

  return 0;
}