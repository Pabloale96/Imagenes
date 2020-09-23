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

  std::cout << "----BMPFileHeader----" << '\n';
  std::cout << "File Type:"<<bmp1.getFileHeader().file_type << '\n';
  std::cout << "File Size:"<<bmp1.getFileHeader().file_size << '\n';
  std::cout << "Reserved1:"<<bmp1.getFileHeader().reserved1 << '\n';
  std::cout << "Reserved2:"<<bmp1.getFileHeader().reserved2 << '\n';
  std::cout << "Offset Data:"<<bmp1.getFileHeader().offset_data << '\n';
  std::cout << "----BMPInfoHeader----" << '\n';
  std::cout << "Size Header:"<<bmp1.getInfoHeader().size << '\n';
  std::cout << "Width:"<<bmp1.getInfoHeader().width << '\n';
  std::cout << "Height:"<<bmp1.getInfoHeader().height << '\n';
  std::cout << "Planes:"<<bmp1.getInfoHeader().planes << '\n';
  std::cout << "Bit Count:"<<bmp1.getInfoHeader().bit_count << '\n';
  std::cout << "Compression:"<<bmp1.getInfoHeader().compression << '\n';
  std::cout << "Size Image:"<<bmp1.getInfoHeader().size_image << '\n';
  std::cout << "X pixels per meter:"<<bmp1.getInfoHeader().x_pixels_per_meter << '\n';
  std::cout << "Y pixels per meter:"<<bmp1.getInfoHeader().y_pixels_per_meter << '\n';
  std::cout << "Colors Used:"<<bmp1.getInfoHeader().colors_used << '\n';
  std::cout << "Colors Important:"<<bmp1.getInfoHeader().colors_important << '\n';

  /*int32_t w = bmp1.getInfoHeader().width/2;
  int32_t h = bmp1.getInfoHeader().height;
  //int32_t x = bmp1.getInfoHeader().x_pixels_per_meter+2e32;
  //int32_t y = bmp1.getInfoHeader().y_pixels_per_meter+2e32;
  //uint32_t s = bmp1.getInfoHeader().size_image*2;
  bmp1.setHeight(h);
  bmp1.setWidth(w);
  //bmp1.setXperPixel(x);
  //bmp1.setYperPixel(y);
  //bmp1.setSizeImage(s);
  w = w*2;
  bmp1.setHeight(h);
  bmp1.setWidth(w);
  bmp1.write("Wdiv2Yvuelvo.bmp");
*/
/*
  bmp1.grayScale();
  bmp1.negative();
  bmp1.write("negativoBlancoyNegro.bmp");
  */
  int32_t w = bmp1.getInfoHeader().width*2;
  int32_t h = bmp1.getInfoHeader().height*2;

  bmp bmp2(h,w,false);
  bmp2.copyData2(bmp1);
  bmp2.write("copiadoDataimagenDobleTamanio.bmp");
  //bmp bmp4(640,480,false);

  //bmp2.copyData(bmp1);
  //bmp4.copyData2(bmp1);
  //bmp1.grayScale();
  //bmp2.grayScale2();
  //std::cout << bmp2.getInfoHeader().bit_count << '\n';

  /*int32_t h=640;
  int32_t w=480;
  int32_t x=100;
  int32_t y=100;

  bmp1.setWidth(h);
  bmp1.setHeight(w);
  bmp1.setXperPixel(x);
  bmp1.setYperPixel(y);*/

  //bmp1.write("blancoNegro.bmp");
  //bmp1.negative();
  //bmp1.write("negativo.bmp");
  //bmp2.write(ofs);
  //bmp2.write("bmp4.bmp");

  //bmp bmp3(640, 480, false);
  //bmp3.fill_region(0, 0, 100, 100, 255, 255, 255, 125);
  //bmp3.write("bmp3.bmp");

  (ifs).close();
  (ofs).close();


  return 0;
}
