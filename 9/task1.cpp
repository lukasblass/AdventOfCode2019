#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

void extendIntcode(std::vector<long long>& intcode, int size) {
  for (int i=intcode.size(); i<size; i++) {
    intcode.push_back(0);
  }
}

int runIntcode(std::vector<long long>& intcode) {
  const double input = 1;
  int relative_base = 0;
  int state = 0;

  while (intcode[state] != 99) {
    int command = intcode[state];
    //std::cout << state << " " << relative_base <<  std::endl;
    // notice that the mode can now be 0,1,2, position, immediate, relative mode
    int arr[] = {0, 0, 0, 0}; // opcode, mode param1, mode param2, mode param3
    arr[0] = command % 10;
    arr[1] = int(command / 100) % 10;
    arr[2] = int(command / 1000) % 10;
    arr[3] = int(command / 10000) % 10;
    long long o1 = 0; long long o2 = 0; 
    int o3; // is always and address

    // first, read the operands given the current parameter mode
    // for o1
    switch(arr[1]) {
      case 0:
        o1 = intcode[intcode[state + 1]];
        break;
      case 1:
        o1 = intcode[state + 1];
        break;
      case 2: 
        o1 = intcode[intcode[state + 1] + relative_base];
        break;
      default:
        std::cout << "invalid param mode for param 1" << std::endl;
    }
    // for o2
    switch(arr[2]) {
      case 0:
        o2 = intcode[intcode[state + 2]];
        break;
      case 1:
        o2 = intcode[state + 2];
        break;
      case 2: 
        o2 = intcode[intcode[state + 2] + relative_base];
        break;
      default:
        std::cout << "invalid param mode for param 2" << std::endl;
    }
    // for o3
    switch(arr[3]) {
      case 0:
        o3 = intcode[intcode[state + 3]];
        break;
      case 2:
        o3 = intcode[intcode[state + 3] + relative_base];
      default:
        std::cout << "read invlaid param mode for param 3, should only be 0 or 2" << std::endl;
    }

    // now execute the actual instruction
    switch (arr[0]) {
      case 1:
        if (o3 > intcode.size()) { extendIntcode(intcode, o3); }
        intcode[o3] = o1 + o2;
        state += 4;
        break;
      case 2:
        if (o3 > intcode.size()) { extendIntcode(intcode, o3); }
        intcode[o3] = o1 * o2;
        state += 4;
        break;
      case 3:
        if (o1 > intcode.size()) { extendIntcode(intcode, o1); }
        intcode[o1] = input;
        state += 2;
        break;
      case 4:
        std::cout << o1 << std::endl;
        state += 2;
        break;
      case 5:
        if (o1 != 0) {
          state = o2;
        } else {
          state += 3;
        }
        break;
      case 6:
        if (o1 == 0) {
          state = o2;
        } else {
          state += 3;
        }
        break;
      case 7:
        if (o3 > intcode.size()) { extendIntcode(intcode, o3); }
        if (o1 < o2) {
          intcode[o3] = 1;
        } else {
          intcode[o3] = 0;
        }
        state += 4;
        break;
      case 8:
        if (o3 > intcode.size()) { extendIntcode(intcode, o3); }
        if (o1 == o2) {
          intcode[o3] = 1;
        } else {
          intcode[o3] = 0;
        }
        state += 4;
        break;
      case 9:
        relative_base += o1;
        state += 2;
        break;
      default:
        std::cout << "invalid opcode" << std::endl;
        break;
    } 
  }
  return -1;  
}


int main() {
  std::ifstream file;
  file.open("input.txt");
  std::string s;
  file >> s;
  std::vector<long long> intcode;
  intcode.reserve(33);
  s = "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99";
  int index = 0;
  int start_index = 0;
  while (index < s.length()) {
    if (s[index] == ',') {
      std::string subs = s.substr(start_index, index - start_index);
      intcode.push_back(std::strtoll(subs.c_str(), nullptr, 10));
      index++;
      start_index = index;
    } else {
      index++;
    }
  }
  intcode.push_back(std::strtoll(s.substr(start_index, s.length() - start_index).c_str(), nullptr, 10));
  int end = intcode.size() * 2; 
  for (int i=0; i<end; i++) {
    intcode.push_back(0);
  }
  std::cout << "hi" << std::endl;
  // for (long long l : intcode) {
  //   std::cout << l << ",";
  // }

  runIntcode(intcode);
}
