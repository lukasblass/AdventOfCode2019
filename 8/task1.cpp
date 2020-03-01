#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>


int doWork(std::string s) {
  
  const int width = 25;
  const int height = 6;
  
  const int layers = s.length() / (width * height);
  //std::cout << layers << std::endl;
  int min_0_digits = width * height;
  int result = -1;
  int min_layer = -1;
  for (int i=0; i<layers; i++) {
    std::vector<int> nr_digits = {0,0,0}; // nr 0s, 1s, 2s
    int start_index = i * (width * height);
    int end_index = start_index  + (width * height);
    
    for (int j = start_index; j < end_index; j++) {
      switch(s[j]) {
        case '0':
          nr_digits[0]++;
          break;
        case '1':
          nr_digits[1]++;
          break;
        case '2':
          nr_digits[2]++;
          break;
        default:
          std::cout << "invalid char" << std::endl;
          break;
      }
    }
    std::cout << nr_digits[0] << " " << nr_digits[1] << "  " << nr_digits[2] << std::endl;
    if (nr_digits[0] < min_0_digits) {
      min_0_digits = nr_digits[0];
      result = nr_digits[1] * nr_digits[2];
      min_layer = i;
    }
  }
  std::cout << min_layer << "min layer " << std::endl;
  return result;
}


int main() {

  std::ifstream f;
  f.open("input.txt");

  std::string input;
  f >> input;
  //std::cout << input << std::endl;
  int res = doWork(input);
  std::cout << res << std::endl;

  return 0;
}