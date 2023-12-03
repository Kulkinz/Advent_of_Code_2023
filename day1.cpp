using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main() {
  cout << "Day 1" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day1.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {

    data.push_back(str);

  }

  int sum = 0;

  for (auto &line : data) {
    string front = "";
    string back = "";
    for (int i = 0; i < line.length(); ++i) {
      char curr = line[i];
      if (isdigit(curr)) {
        front.push_back(line[i]);
        break;
      } else {
        if (line.find("one") == i) {
          front = "1";
          break;
        } else if (line.find("two") == i) {
          front = "2";
          break;
        } else if (line.find("three") == i) {
          front = "3";
          break;
        } else if (line.find("four") == i) {
          front = "4";
          break;
        } else if (line.find("five") == i) {
          front = "5";
          break;
        } else if (line.find("six") == i) {
          front = "6";
          break;
        } else if (line.find("seven") == i) {
          front = "7";
          break;
        } else if (line.find("eight") == i) {
          front = "8";
          break;
        } else if (line.find("nine") == i) {
          front = "9";
          break;
        }
      }
    }
    reverse(line.begin(), line.end());
    for (int i = 0; i < line.length(); ++i) {

      char curr = line[i];
      if (isdigit(curr)) {
        back.push_back(line[i]);
        break;
      } else {
        if (line.find("eno") == i) {
          back = "1";
          break;
        } else if (line.find("owt") == i) {
          back = "2";
          break;
        } else if (line.find("eerht") == i) {
          back = "3";
          break;
        } else if (line.find("ruof") == i) {
          back = "4";
          break;
        } else if (line.find("evif") == i) {
          back = "5";
          break;
        } else if (line.find("xis") == i) {
          back = "6";
          break;
        } else if (line.find("neves") == i) {
          back = "7";
          break;
        } else if (line.find("thgie") == i) {
          back = "8";
          break;
        } else if (line.find("enin") == i) {
          back = "9";
          break;
        }
      }
    }
    string num = front + back;
    sum += stoi(num);
  }

  cout << sum << endl;

  return sum;
}