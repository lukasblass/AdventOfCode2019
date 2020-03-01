#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Amplifier {
  Amplifier(std::vector<int> ic, int ph) : 
      intcode(ic), phase(ph), state(0), reached_halting_state(false),
      phase_as_input(true) {}
  std::vector<int> intcode;
  int phase;
  int state;
  int output; // the computed output
  bool reached_halting_state;
  bool phase_as_input;
};  

void runIntcode(Amplifier& amp, const int input) {
  std::vector<int>& intcode = amp.intcode;
  int& state = amp.state;

  while (intcode[state] != 99) {
    int command = intcode[state];

    int arr[] = {0, 0, 0, 0}; // opcode, mode param1, mode param2, mode param3
    arr[0] = command % 10;
    arr[1] = int(command / 100) % 10;
    arr[2] = int(command / 1000) % 10;
    arr[3] = int(command / 10000) % 10;
    int o1 = 0; int o2 = 0;
    switch (arr[0]) {
      case 1: // addition
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        intcode[intcode[state + 3]] = o1 + o2;
        state += 4;
        break;
      case 2: // multiplication
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        intcode[intcode[state + 3]] = o1 * o2;
        state += 4;
        break;
      case 3: // input
        if (amp.phase_as_input) {
          intcode[intcode[state + 1]] = amp.phase;
          amp.phase_as_input = false;
        } else {
          intcode[intcode[state + 1]] = input;
        }
        state += 2;
        break;
      case 4: // output
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        state += 2;
        amp.output = o1;
        return;
        break;
      case 5: // jump non zero
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 != 0) {
          state = o2;
        } else {
          state += 3;
        }
        break;
      case 6: // jump zero
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 == 0) {
          state = o2;
        } else {
          state += 3;
        }
        break;
      case 7: // write if leq
        o1 = arr[1] == 0 ? intcode[intcode[state + 1]] : intcode[state + 1];
        o2 = arr[2] == 0 ? intcode[intcode[state + 2]] : intcode[state + 2];
        if (o1 < o2) {
          intcode[intcode[state + 3]] = 1;
        } else {
          intcode[intcode[state + 3]] = 0;
        }
        state += 4;
        break;
      case 8: // write if eq
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
  // we reached the halting state => set the flag
  amp.reached_halting_state = true;
}

int runAmplifiers(std::vector<int> intcode, std::vector<int> phases) {
  
  // set up the amplifiers
  std::vector<Amplifier> amps;
  for (int i=0; i<5; i++) {
    amps.push_back(Amplifier(intcode, phases[i]));
  }

  int input = 0;
  bool done = false;
  while (!done) {
    for (int i=0; i<5; i++) {
      runIntcode(amps[i], input);
      input = amps[i].output;
    }
    done = true;
    for (int i=0; i<5; i++) {
      done &= amps[i].reached_halting_state;
    }
  }
  return amps[4].output;
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

  std::vector<std::vector<int>> permutations = generatePermutations({5,6,7,8,9});

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