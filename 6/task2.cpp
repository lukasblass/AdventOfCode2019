#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>

struct Planet {
  Planet(std::string p) : name(p) {}
  std::string name;
  std::vector<Planet*> direct_orbits; // planets that directly orbit this planet

  bool operator==(Planet& other) {
    return name == other.name;
  }
};

std::vector<int> computeNrOrbits(Planet* planet) {
  std::vector<int> orbits;
  if (planet->direct_orbits.size() == 0) {
    orbits.push_back(0);
    return orbits;
  }
  
  for (Planet* p : planet->direct_orbits) {
    std::vector<int> temp_orbits = computeNrOrbits(p);
    for (auto o : temp_orbits) {
      orbits.push_back(o + 1);
    }
  }
  orbits.push_back(0);
  return orbits;
}

int getDistanceTo(Planet* p, std::string s) {
  if (p->direct_orbits.size() == 0) {
    return -1; // not connected
  }

  bool found = false;
  int min_dist = 20000;
  for (Planet* pl : p->direct_orbits) {
    if (pl->name == s) {
      return 0; // directly connected
    } else {
      int d = getDistanceTo(pl, s);
      if (d >= 0 && d < min_dist) {
        found = true;
        min_dist = d + 1;
      }
    }
  }
  if (found) {
    return min_dist;
  } else {
    return -1; // not connected
  }
}

int findMinDistance(Planet *p) {

  if (p->direct_orbits.size() == 0) {
    return -1;
  }
  
  // first we find for all children the best distance
  int mindist = 20000;
  bool valid_child_dist = false;
  for (Planet *pl : p->direct_orbits) {
    int dist = findMinDistance(pl);
    if (dist >= 0 && dist < mindist) {
      mindist = dist;
      valid_child_dist = true;
    }
  }

  // then we check the distance we have ourselves
  int distanceToSanta = getDistanceTo(p, "SAN");
  int distanceToYou = getDistanceTo(p, "YOU");
  bool valid_self_dist = distanceToSanta >= 0 && distanceToYou >= 0;
  int self_dist = distanceToSanta + distanceToYou;

  if (valid_self_dist && valid_child_dist) {
    return std::min(self_dist, mindist);
  } else if (valid_self_dist) {
    return self_dist;
  } else if (valid_child_dist) {
    return mindist;
  } else {
    return -1;
  }
}

int main() {

  std::ifstream file;
  file.open("input.txt");

  std::string line;
  std::map<std::string, Planet*> map;
  while (file >> line) {
    int idx = 0;
    while (line[idx] != ')') {
      idx++;
    }
    std::string planet1 = line.substr(0, idx);
    std::string planet2 = line.substr(idx + 1, line.size() - planet1.size() - 1);
    
    if (map.find(planet1) == map.end()) {
      map.insert(std::pair<std::string,Planet*>(planet1, new Planet(planet1)));
    }
    if (map.find(planet2) == map.end()) {
      map.insert(std::pair<std::string,Planet*>(planet2, new Planet(planet2)));
    }
    map[planet1]->direct_orbits.push_back(map[planet2]);
  }
 
  // int distanceToSanta = getDistanceTo(map["D"], "SAN");
  // int distanceToYou = getDistanceTo(map["D"], "YOU");
  // std::cout << distanceToYou <<  " " <<  distanceToSanta << std::endl;

  int d = findMinDistance(map["COM"]);
  std::cout << d << std::endl;
  // std::vector<int> orbits = computeNrOrbits(map["COM"]);
  // int result = 0;
  // for (int o : orbits) {
  //   result += o;
  // }

  //std::cout << result << std::endl;
  return 0;
}