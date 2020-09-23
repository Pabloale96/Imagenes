#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <limits>
#include <ctime>
#include <vector>
#include <cstdint>

using namespace std;

int main(int argc, char const *argv[])
{
  vector<vector<int>> data;

  std::cout << "data" << '\n';
  std::cout << data.size()<< '\n';

  data.resize(5);

  std::cout << "data" << '\n';
  std::cout << data.size()<< '\n';

  for (size_t i = 0; i < data.size(); i++) {
    data[i].resize(3);
  }
  std::cout << "data" << '\n';
  std::cout << data[0].size()<< '\n';
  for (size_t i = 0; i < data[0].size(); i++) {
    for (size_t j = 0; j < data.size(); j++) {
      data[j][i]=i+j;
    }
  }

  for (size_t i = 0; i < data[0].size(); i++) {
    for (size_t j = 0; j < data.size(); j++) {
        std::cout << data[j][i];
    }
    std::cout << '\n';
  }

  return 0;
}
