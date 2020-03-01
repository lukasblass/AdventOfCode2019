#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

struct Location {
  Location(std::pair<int,int> p, int d) : pos(p), dist(d) {}
  std::pair<int,int> pos;
  int dist;
};

std::vector<Location> extractCorners(std::string& s) {
  std::vector<Location> locs;
  std::pair<int,int> curpos(0,0);
  int distance = 0;
  int index = 0;
  int start_index = 0;
  
  while (index < s.length()) {
    if (s[index] == ',') {
      std::string subs = s.substr(start_index, index - start_index);
      char direction = subs[0];
      int length = std::stoi(subs.substr(1, subs.length() - 1));
      switch (direction) {
        case 'R':
          for (int i=0; i<length; i++) {
            curpos.first += 1;
            distance++;
            locs.push_back(Location(curpos, distance));
          }
          break;
        case 'L':
          for (int i=0; i<length; i++) {
            curpos.first -= 1;
            distance++;
            locs.push_back(Location(curpos, distance));
          }
          break;
        case 'U':
          for (int i=0; i<length; i++) {
            curpos.second += 1;
            distance++;
            locs.push_back(Location(curpos, distance));
          }
          break;
        case 'D':
          for (int i=0; i<length; i++) {
            curpos.second -= 1;
            distance++;
            locs.push_back(Location(curpos, distance));
          }
          break;
        default:
          curpos.second += 0;
          break;
      }      
      index++;
      start_index = index;
    } else {
      index++;
    }
  }
  return locs;
}

bool func(Location& l1, Location& l2) {
  std::pair<int,int> p1 = l1.pos;
  std::pair<int,int> p2 = l2.pos;
  if (p1.first < p2.first) {
    return true;
  } else if (p2.first < p1.first) {
    return false;
  } else {
    return p1.second <= p2.second;
  }
}

int main() {
  std::ifstream file;
  file.open("input.txt");
  std::string s1, s2;
  file >> s1;
  file >> s2;
  
  std::vector<Location> p1s = extractCorners(s1);
  std::sort(p1s.begin(), p1s.end(), func);

  std::vector<Location> p2s = extractCorners(s2);
  std::sort(p2s.begin(), p2s.end(), func);

  double mindist = 200000;
  int index1 = 0;
  int index2 = 0;
  while (index1 < p1s.size()) {
    Location p1 = p1s[index1];
    while (index2 < p2s.size() && func(p2s[index2], p1)) { // run until we find a element of p2 that's larger than p1
      Location p2 = p2s[index2];
      if (p1.pos.first == p2.pos.first && p1.pos.second == p2.pos.second) {
        if (p1.dist + p2.dist < mindist) {
          mindist = p1.dist + p2.dist;
        }
      }
      index2++;
    }
    index1++;
  }
  std::cout << mindist << std::endl;
  return 0;
}