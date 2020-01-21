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
  bmp bmp2(640,480,false);

  bmp2.copyData(bmp1);

  //std::cout << bmp2.getInfoHeader().bit_count << '\n';

  int32_t h=640;
  int32_t w=480;
  int32_t x=100;
  int32_t y=100;

  bmp1.setWidth(h);
  bmp1.setHeight(w);
  bmp1.setXperPixel(x);
  bmp1.setYperPixel(y);

  bmp1.write("x_y_per_pixel.bmp");
  bmp2.write(ofs);

  bmp bmp3(640, 480, false);
  bmp3.fill_region(0, 0, 100, 100, 255, 255, 255, 125);
  bmp3.write("bmp3.bmp");

  (ifs).close();
  (ofs).close();


  return 0;
}
