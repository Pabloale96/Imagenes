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

#include "cmdline.h"
#include "options.h"
#include "bmp.h"


using namespace std;

int main(int argc, char const *argv[])
{
  cmdline cmdl(options);
  cmdl.parse(argc, argv);

  bmp bmp1(ifs);
  bmp bmp2(500,500,false);

  bmp2.copyData(bmp1);

  std::cout << bmp1.getFileHeader().offset_data<< '\n';
  std::cout << bmp2.getFileHeader().offset_data << '\n';

  bmp1.write("copia.bmp");
  bmp2.write(ofs);

  bmp bmp3(500, 500, false);
  bmp3.fill_region(0, 0, 100, 100, 255, 255, 255, 125);
  bmp3.write("bmp3.bmp");

  (ifs).close();
  (ofs).close();


  return 0;
}
