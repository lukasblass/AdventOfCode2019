#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

int getFuelNeeded(const int mass) {
  int ret = mass / 3;
  return ret - 2;
}

int main() {
  std::ifstream file;
  file.open("task1.txt");

  std::string line;
  int sum = 0;
  while (file >> line) {
    int fuel = getFuelNeeded(std::stoi(line));
    sum += fuel;
    int fuel_of_fuel = getFuelNeeded(fuel);
    while (fuel_of_fuel > 0) {
      sum += fuel_of_fuel;
      fuel_of_fuel = getFuelNeeded(fuel_of_fuel);
    }
  }

  std::cout << "sum: " << sum << std::endl;


  return 0;


}