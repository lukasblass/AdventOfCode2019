#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>


std::vector<int> doWork(std::string s, const int width, const int height) {
  
  const int blocksize = width * height;
  std::vector<int> image(blocksize);
  
  const int layers = s.length() / blocksize;
  std::cout << "lazers: " << layers << std::endl;

  for (int i=0; i<blocksize; i++) {
    int color = -1;
    int layer = 0;
    while (color == -1 ) {
      char c = s[i + layer * blocksize];
      switch (c) {
        case '0':
          color = 0;
          //std::cout << "found color 0" << std::endl;
          break;
        case '1': 
          color = 1;
          //std::cout << "found color 1" << std::endl;
          break;
        default:
          // not setting any color
          break;
      }
      layer++;
    }
    if (color == -1) {
      std::cout << "error" << std::endl;
    } else {
      //std::cout << "no error: " << color << std::endl;
      image[i] = color;
    }
  }
  return image;
}


int main() {

  std::ifstream f;
  f.open("input.txt");

  std::string input;
  f >> input;
  //input = "0222112222120000";
  
  const int width = 25;
  const int height = 6;
  std::vector<int> res = doWork(input, width, height);

  for (int i = 0; i < height; i++) {
    for (int j=0; j<width; j++) {
      if (res[i * width + j] == 0) {
        std::cout << " ";
      } else {
        std::cout << "#";
      }

    }
    std::cout << std::endl;
  }
  //std::cout << "\n" <<  res.size() << std::endl;

  return 0;
}