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
    sum += getFuelNeeded(std::stoi(line));
  }
  std::cout << "sum: " << sum << std::endl;
  return 0;


}