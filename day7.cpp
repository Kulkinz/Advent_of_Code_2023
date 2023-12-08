using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "Helpers/HelperFunctions.h"

struct camel {
  string hand;
  int bid;
};

int getType(const camel& a) {
  map<char, int> chars;
  for (int i = 0; i < a.hand.size(); i++) {
    chars[a.hand[i]]++;
  }
  vector<int> values;
  if (chars['J'] == 0) {
    for ( const auto &[key, value]: chars ) {
      values.push_back(value);
    }
    if (contains(values, 5)) { // five of a kind
      return 7;
    }
    if (contains(values, 4)) { // four of a kind
      return 6;
    }
    if (contains(values, 3) && contains(values, 2)) { // full house
      return 5;
    }
    if (contains(values, 3)) { // three of a kind
      return 4;
    }
    if (contains(values, 2)) {
      if (count(values.begin(), values.end(), 2) == 2) { // two pair
        return 3;
      } else {
        return 2; // one pair
      }
    }
    return 1; // high card
  } else {
    int J = 0;
    for ( const auto &[key, value]: chars ) {
      if (key == 'J') {
        J = value;
      } else {
        values.push_back(value);
      }
    }
    if (J == 5) { // five of a kind // JJJJJ
      return 7;
    }
    if (J == 4) { // five of a kind // JJJJX
      return 7;
    }
    if (J == 3) {
      if (contains(values, 2)) {
        return 7; // five of a kind // JJJXX
      } else {
        return 6; // four of a kind // JJJXY
      }
    }
    if (J == 2) {
      if (contains(values, 3)) {
        return 7; // five of a kind // JJXXX
      }
      if (contains(values, 2)) {
        return 6; // four of a kind // JJXXY
      } else {
        return 4; // three of a kind // JJXYZ
      }
    }
    if (J == 1) {
      if (contains(values, 4)) {
        return 7; // five of a kind // JXXXX
      }
      if (contains(values, 3)) {
        return 6; // four of a kind // JXXXY
      }
      if (contains(values, 2)) {
        if (count(values.begin(), values.end(), 2) == 2) { // two pair
          return 5; // full house // JXXYY
        } else {
          return 4; // three of a kind // JXXYZ
        }
      }
      return 2; // one pair // JXYZA
    }
    return 1;
  }
}

static int getCardValue(char n) {
  switch(n) {
    case 'A': return 13;
    case 'K': return 12;
    case 'Q': return 11;
    case 'T': return 10;
    case '9': return 9;
    case '8': return 8;
    case '7': return 7;
    case '6': return 6;
    case '5': return 5;
    case '4': return 4;
    case '3': return 3;
    case '2': return 2;
    case 'J': return 1;
    default: return 0;
  }
}

bool operator<(const camel& a, const camel& b) {
  if (getType(a) != getType(b)) {
    return (getType(a) < getType(b));
  }

  for (int i = 0; i < a.hand.size(); i++) {
    if (getCardValue(a.hand[i]) != getCardValue(b.hand[i])) {
      return getCardValue(a.hand[i]) < getCardValue(b.hand[i]);
    }
  }

  return false;
}

int main() {
  cout << "Day 7" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day7.txt)");
  string str;

  vector<camel> data;

  while (getline(file, str)) {
    cout << str << endl;
    vector<string> out;
    tokenize(str, ' ', out);
    data.push_back({out[0], stoi(out[1])});
  }

  cout << " --- " << endl;

  sort(data.begin(), data.end());

  long long sum = 0;

  for (int i = 0; i < data.size(); ++i) {
    cout << i+1 << " - " << data[i].hand << " - " << getType(data[i]) << endl;
    sum += (i+1)*data[i].bid;
  }

  cout << sum << endl;

  return 0;
}
