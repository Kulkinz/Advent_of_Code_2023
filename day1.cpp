using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  cout << "Day 1" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day1.txt)");
  string str;

  while (getline(file, str)) {
    cout << str << endl;
  }

  return 0;
}