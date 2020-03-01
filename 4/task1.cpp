#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

bool isValidPw(int i) {
  std::vector<int> vec_i(6);
  for (int idx = 5; idx >= 0; --idx) {
    vec_i[5-idx] = int((i / pow(10, idx))) % 10;
  }

  bool increasing = true;
  // check increasing
  for (int idx = 0; idx < 5; ++idx) {
    if (vec_i[idx] > vec_i[idx + 1]) {
      increasing = false;
    }
  }

  // check pair
  bool has_pair = false;
  for (int idx = 0; idx < 5; ++idx) {
    if (vec_i[idx] == vec_i[idx + 1]) {
      has_pair = true;
    }
  }
  return increasing && has_pair;
}

int main() {
  int lower = 271973;
  int higher = 785961;
  int nr_valid_pw = 0;

  for (int i = lower; i <= higher; i++) {
   nr_valid_pw += isValidPw(i) ? 1 : 0;
  }
  std::cout << nr_valid_pw << std::endl; // answer: 1660
  return 0;
}