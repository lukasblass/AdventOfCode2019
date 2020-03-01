#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// void runIntcode(std::vector<int>& intcode) {
//   int state = 0;
//   int command = intcode[state];
//   while (command != 99) {
//     int o1 = intcode[intcode[state + 1]];
//     int o2 = intcode[intcode[state + 2]];
//     if (command == 1) {
//       intcode[intcode[state + 3]] = o1 + o2;
//     } else {
//       intcode[intcode[state + 3]] = o1 * o2;
//     }
//     state += 4;
//     command = intcode[state];
//   }
// }


void runIntcode(std::vector<int>& intcode) {
  int state = 0;
  
  while (intcode[state] != 99) {
    int command = intcode[state];

    int arr[] = {0, 0, 0, 0}; // opcode, mode param1, mode param2, mode param3
    arr[0] = command % 10;
    arr[1] = int(command / 100) % 10;
    arr[2] = int(command / 1000) % 10;
    arr[3] = int(command / 10000) % 10;
    int o1 = 0; int o2 = 0;
    const int input = 5;
    switch (arr[0]) {
      case 1:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        intcode[intcode[state + 3]] = o1 + o2;
        state += 4;
        break;
      case 2:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        intcode[intcode[state + 3]] = o1 * o2;
        state += 4;
        break;
      case 3:
        intcode[intcode[state + 1]] = input;
        state += 2;
        break;
      case 4:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        std::cout << o1 << " " << std::endl;
        state += 2;
        break;
      case 5:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 != 0) {
          state = o2;
        } else {
          state += 3;
        }
        break;
      case 6:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 == 0) {
          state = o2;
        } else {
          state += 3;
        }
        break;
      case 7:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 < o2) {
          intcode[intcode[state + 3]] = 1;
        } else {
          intcode[intcode[state + 3]] = 0;
        }
        state += 4;
        break;
      case 8:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 == o2) {
          intcode[intcode[state + 3]] = 1;
        } else {
          intcode[intcode[state + 3]] = 0;
        }
        state += 4;
        break;
      default:
        std::cout << "invalid opcode" << std::endl;
        break;
    } 
  }
}

int main() {
  std::ifstream file;
  file.open("input.txt");
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

  runIntcode(intcode);
  return 0;
}