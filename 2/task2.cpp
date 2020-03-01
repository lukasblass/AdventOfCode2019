#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int runIntcode(std::vector<int> intcode, 
        const int noun, const int verb) {
  intcode[1] = noun;
  intcode[2] = verb;
  int state = 0;
  int command = intcode[state];
  while (command != 99) {
    int o1 = intcode[intcode[state + 1]];
    int o2 = intcode[intcode[state + 2]];
    if (command == 1) {
      intcode[intcode[state + 3]] = o1 + o2;
    } else {
      intcode[intcode[state + 3]] = o1 * o2;
    }
    state += 4;
    command = intcode[state];
  }
  return intcode[0];
}

int main() {
  std::ifstream file;
  file.open("task1.txt");
  std::string s;
  file >> s;
  std::vector<int> intcode;
  
  int index = 0;
  int start_index = 0;
  while (index < s.length()) {
    if (s[index] == ',') {
      std::string subs = s.substr(start_index, index - start_index);
      intcode.push_back(std::stoi(subs));
      index++;
      start_index = index;
    } else {
      index++;
    }
  }
  intcode.push_back(std::stoi(s.substr(start_index, s.length() - start_index)));
  
  intcode[1] = 12;
  intcode[2] = 2;
  
  int target = 19690720;
  bool done = false;
  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      int out = runIntcode(intcode, noun, verb);
      if (out == target) {
        std::cout << "answer: " << 100 * noun + verb << std::endl;
        done = true;
        break;
      }    
    }
    if (done) {
      break;
    }
  }

  return 0;
}