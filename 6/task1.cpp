#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

struct Planet {
  Planet(std::string p) : name(p) {}
  std::string name;
  std::vector<Planet*> direct_orbits; // planets that directly orbit this planet
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

int main() {

  std::ifstream file;
  file.open("input.txt");

  std::string line;
  int counter = 0;
  std::map<std::string, Planet*> map;
  bool first = false;
  while (file >> line) {
    int namesize = 3;
    std::string planet1 = line.substr(0, namesize);
    std::string planet2 = line.substr(namesize + 1, namesize);
    if (first) {
      planet1 = line.substr(0, 3);
      planet2 = line.substr(4, 1);
      first = false;
    }
    
    if (map.find(planet1) == map.end()) {
      map.insert(std::pair<std::string,Planet*>(planet1, new Planet(planet1)));
    }

    if (map.find(planet2) == map.end()) {
      map.insert(std::pair<std::string,Planet*>(planet2, new Planet(planet2)));
    }
    map[planet1]->direct_orbits.push_back(map[planet2]);
    counter++;
  }
  // std::cout << map.size() << std::endl;
  // std::cout << "done maping" << std::endl;
  // std::cout << counter << std::endl;
  std::vector<int> orbits = computeNrOrbits(map["COM"]);
  int result = 0;
  for (int o : orbits) {
    result += o;
  }

  std::cout << result << std::endl;
  return 0;
}