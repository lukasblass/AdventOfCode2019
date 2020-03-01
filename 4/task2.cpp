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
  if (!increasing) {
    return false;
  }

  // check pair
  bool has_pair = false;
  int index = 0;
  while (index < 6) {
    int v = vec_i[index];
    int streak = 0;
    while (index + streak + 1 < 6 && vec_i[index + streak + 1] == v) {
      streak++;
    }
    if (streak == 1) {
      has_pair = true;
    }
    index += streak + 1;
  }
  return has_pair;
}

int main() {
  int lower = 271973;
  int higher = 785961;
  int nr_valid_pw = 0;

  for (int i = lower; i <= higher; i++) {
    nr_valid_pw += isValidPw(i) ? 1 : 0;
  }
  std::cout << nr_valid_pw << std::endl;
  return 0;
}