#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int runIntcode(std::vector<int>& intcode, const int phase, const int input) {
  int state = 0;
  bool first_input = true;

  while (intcode[state] != 99) {
    int command = intcode[state];

    int arr[] = {0, 0, 0, 0}; // opcode, mode param1, mode param2, mode param3
    arr[0] = command % 10;
    arr[1] = int(command / 100) % 10;
    arr[2] = int(command / 1000) % 10;
    arr[3] = int(command / 10000) % 10;
    int o1 = 0; int o2 = 0;
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
        if (first_input) {
          intcode[intcode[state + 1]] = phase;
          first_input = false;
        } else {
          intcode[intcode[state + 1]] = input;
        }
        state += 2;
        break;
      case 4:
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        return o1;
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
  return -1;  
}

int runAmplifiers(std::vector<int> intcode, std::vector<int> phases) {
  int input = 0;
  for (int i=0; i<5; i++) {
    input = runIntcode(intcode, phases[i], input);
  }
  return input;
}

std::vector<std::vector<int>> generatePermutations(std::vector<int> numbers) {
  std::vector<std::vector<int>> res;
  if (numbers.size() == 1) {
    std::vector<int> v = {numbers[0]};
    res.push_back(v);
    return res;
  }
  for (int i=0; i<numbers.size(); i++) {
    // put this number in first spot. 
    int val = numbers[i];
    
    std::vector<int> leftover_numbers;
    for (int j=0; j<numbers.size(); j++) {
      if (j != i) {
        leftover_numbers.push_back(numbers[j]);
      }
    }
    std::vector<std::vector<int>> pers = generatePermutations(leftover_numbers);
    for (std::vector<int> v : pers) {
      v.emplace(v.begin(), val);
      res.push_back(v);
    }
  }
  return res;
}

int main() {
  std::ifstream file;
  file.open("input.txt");
  std::string s;
  file >> s;
  //s = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0";
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

  std::vector<std::vector<int>> permutations = generatePermutations({0,1,2,3,4});
  // for (auto per : permutations) {
  //   for (int n : per) {
  //     std::cout << n;
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << "nr pers  " <<  permutations.size() << std::endl;

  int max = -1;
  for (std::vector<int> permutation : permutations) {
    int output = runAmplifiers(intcode, permutation);
    if (output > max) {
      max = output;
    }
  }
  std::cout << max << std::endl;
  return 0;
}