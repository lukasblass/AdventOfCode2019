#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

std::vector<std::pair<int,int>> extractCorners(std::string& s) {
  std::vector<std::pair<int,int>> positions;
  std::pair<int,int> curpos(0,0);

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
            positions.push_back(curpos);
          }
          break;
        case 'L':
          for (int i=0; i<length; i++) {
            curpos.first -= 1;
            positions.push_back(curpos);
          }
          break;
        case 'U':
          for (int i=0; i<length; i++) {
            curpos.second += 1;
            positions.push_back(curpos);
          }
          break;
        case 'D':
          for (int i=0; i<length; i++) {
            curpos.second -= 1;
            positions.push_back(curpos);
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
  return positions;
}

bool func(std::pair<int,int> p1, std::pair<int,int> p2) {
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
  
  std::vector<std::pair<int,int>> p1s = extractCorners(s1);
  std::sort(p1s.begin(), p1s.end(), func);

  std::vector<std::pair<int,int>> p2s = extractCorners(s2);
  std::sort(p2s.begin(), p2s.end(), func);

  double mindist = 200000;
  int index1 = 0;
  int index2 = 0;
  while (index1 < p1s.size()) {
    std::pair<int,int> p1 = p1s[index1];
    while (index2 < p2s.size() && func(p2s[index2], p1)) { // run until we find a element of p2 that's larger than p1
      std::pair<int,int> p2 = p2s[index2];
      if (p1.first == p2.first && p1.second == p2.second) {
        int x = p1.first < 0 ? -p1.first : p1.first;
        int y = p1.second < 0 ? -p1.second : p1.second;
        if (x + y < mindist) {
          mindist = x + y;
        }
      }
      index2++;
    }
    index1++;
  }
  std::cout << mindist << std::endl;
  return 0;
}