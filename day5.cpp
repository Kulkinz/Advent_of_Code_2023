using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "Helpers/HelperFunctions.h"

struct chunk
{
  long long memoryStart, addressStart, size;

  bool operator=(const chunk &o) const {
    return addressStart == o.addressStart && memoryStart == o.memoryStart && size == o.size;
  }

  bool operator<(const chunk &o) const {
    return addressStart < o.addressStart;
  }

  bool operator() (const chunk &a, const chunk &b) {
    return (a<b);
  }
};

long long int getLocation(long long int seed);
long long int getSeed(long long int location);
bool seedInRange(const vector<long long int> &seeds, long long int seed);
long long mapValue(vector<chunk> &mapping, long long value) {
  for (auto &map : mapping) {
    if (value >= map.addressStart && value < (map.addressStart + map.size)) {
      return map.memoryStart + (value - map.addressStart);
    }
  }
  return value;
}

long long mapValueReverse(vector<chunk> &mapping, long long value) {
  for (auto &map : mapping) {
    if (value >= map.memoryStart && value < (map.memoryStart + map.size)) {
      return map.addressStart + (value - map.memoryStart);
    }
  }
  return value;
}

vector<chunk> seedSoilMap;
vector<chunk> soilFertilizerMap;
vector<chunk> fertilizerWaterMap;
vector<chunk> waterLightMap;
vector<chunk> lightTemperatureMap;
vector<chunk> temperatureHumidityMap;
vector<chunk> humidityLocationMap;
int main() {
  cout << "Day 5" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2023\inputs\day5.txt)");
  string str;

  vector<string> data;

  // data - 0

  // seed-to-soil - 1
  // soil-to-fertilizer - 2
  // fertilizer-to-water - 3
  // water-to-light - 4
  // light-to-temperature - 5
  // temperature-to-humidity - 6
  // humidity-to-location - 7

  int x = 0;
  vector<long long> seeds;
  while (getline(file, str)) {
    if (str == "") {
      x++;
      continue;
    }
    vector<string> out;
    tokenize(str, ' ', out);
    switch (x) {
      case 0:
        for (int i = 1; i < out.size(); i++) {
          seeds.push_back(stoll(out[i]));
        }
        break;
      case 1:
        if (out.size() == 3) {
          seedSoilMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      case 2:
        if (out.size() == 3) {
          soilFertilizerMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      case 3:
        if (out.size() == 3) {
          fertilizerWaterMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      case 4:
        if (out.size() == 3) {
          waterLightMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      case 5:
        if (out.size() == 3) {
          lightTemperatureMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      case 6:
        if (out.size() == 3) {
          temperatureHumidityMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      case 7:
        if (out.size() == 3) {
          humidityLocationMap.push_back({stoll(out[0]), stoll(out[1]), stoll(out[2])});
        }
        break;
      default:
        break;
    }
  }
  sort(seedSoilMap.begin(), seedSoilMap.end());
  sort(soilFertilizerMap.begin(), soilFertilizerMap.end());
  sort(fertilizerWaterMap.begin(), fertilizerWaterMap.end());
  sort(waterLightMap.begin(), waterLightMap.end());
  sort(lightTemperatureMap.begin(), lightTemperatureMap.end());
  sort(temperatureHumidityMap.begin(), temperatureHumidityMap.end());
  sort(humidityLocationMap.begin(), humidityLocationMap.end());

  // seed-to-soil - 1
  // soil-to-fertilizer - 2
  // fertilizer-to-water - 3
  // water-to-light - 4
  // light-to-temperature - 5
  // temperature-to-humidity - 6
  // humidity-to-location - 7
  long long lowest = LONG_LONG_MAX;
  for (auto &seed : seeds) {
    lowest = min(lowest, getLocation(seed));
  }

  long long lowestTotal = LONG_LONG_MAX;

  cout << "Part 1: " << lowest << endl;

  long long smallestRange = LONG_LONG_MAX; // optimization
  for (int i = 1; i < seeds.size(); i+=2) { smallestRange = min(smallestRange, seeds[i]); }
  for (auto &it : seedSoilMap) { smallestRange = min(smallestRange, it.size); }
  for (auto &it : soilFertilizerMap) { smallestRange = min(smallestRange, it.size); }
  for (auto &it : fertilizerWaterMap) { smallestRange = min(smallestRange, it.size); }
  for (auto &it : waterLightMap) { smallestRange = min(smallestRange, it.size); }
  for (auto &it : lightTemperatureMap) { smallestRange = min(smallestRange, it.size); }
  for (auto &it : temperatureHumidityMap) { smallestRange = min(smallestRange, it.size); }
  for (auto &it : humidityLocationMap) { smallestRange = min(smallestRange, it.size); }

  long long focalPoint;
  for (long long int n = 0; ; n += smallestRange) {
    long long seed = getSeed(n);
    if (seedInRange(seeds, seed)) {
      focalPoint = n;
      break;
    }
  }
  while (seedInRange(seeds, getSeed(focalPoint - 1))) {
    focalPoint--;
  }

  cout << "Part 2: " << focalPoint << endl;

  return 0;
}
bool seedInRange(const vector<long long int> &seeds, long long int seed) {
  for (int i = 0; i < seeds.size(); i+=2) {
    if (seed >= seeds[i] && seed < (seeds[i] + seeds[i+1])) {
      return true;
    }
  }
  return false;
}
long long int getLocation(long long int seed) {
  long long soil = mapValue(seedSoilMap, seed);
  long long fertilizer = mapValue(soilFertilizerMap, soil);
  long long water = mapValue(fertilizerWaterMap, fertilizer);
  long long light = mapValue(waterLightMap, water);
  long long temperature = mapValue(lightTemperatureMap, light);
  long long humidity = mapValue(temperatureHumidityMap, temperature);
  long long location = mapValue(humidityLocationMap, humidity);
  return location;
}

long long int getSeed(long long int location) {
  long long humidity = mapValueReverse(humidityLocationMap, location);
  long long temperature = mapValueReverse(temperatureHumidityMap, humidity);
  long long light = mapValueReverse(lightTemperatureMap, temperature);
  long long water = mapValueReverse(waterLightMap, light);
  long long fertilizer = mapValueReverse(fertilizerWaterMap, water);
  long long soil = mapValueReverse(soilFertilizerMap, fertilizer);
  long long seed = mapValueReverse(seedSoilMap, soil);
  return seed;
}
