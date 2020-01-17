#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>
#include <cstdint>

#include "bmp.h"


bmp::bmp(const fstream input){
  //Leo el file header:
  input.read((char *) &(*this.bmpfileheader.bfType), sizeof(*this.bmpfileheader.bfType));//leo el tipo del archivo

  // Reviso el formato:
  if (*this.bmpfileheader.bfType != 0x4d42) {
    throw std::runtime_error("ERROR: formato desconocido.");
  }
  input.read((char *) &(*this.bmpfileheader.bfSize),sizeof(*this.bmpfileheader.bfSize));
  input.read((char *) &(*this.bmpfileheader.bfReserved1),sizeof(*this.bmpfileheader.bfReserved1));
  input.read((char *) &(*this.bmpfileheader.bfReserved2),sizeof(*this.bmpfileheader.bfReserved2));
  input.read((char *) &(*this.bmpfileheader.bfIffBits),sizeof(*this.bmpfileheader.bfIffBits));

  //Leo el info header:
  input.read((char *) &(*this.bmpinfoheader.bit_size),sizeof(*this.bmpinfoheader.bit_size));
  input.read((char *) &(*this.bmpinfoheader.bit_width),sizeof(*this.bmpinfoheader.bit_width));
  input.read((char *) &(*this.bmpinfoheader.bit_height),sizeof(*this.bmpinfoheader.bit_height));
  input.read((char *) &(*this.bmpinfoheader.planes),sizeof(*this.bmpinfoheader.planes));
  input.read((char *) &(*this.bmpinfoheader.bit_count),sizeof(*this.bmpinfoheader.bit_count));
  input.read((char *) &(*this.bmpinfoheader.compression),sizeof(*this.bmpinfoheader.compression));
  input.read((char *) &(*this.bmpinfoheader.image_size),sizeof(*this.bmpinfoheader.image_size));
  input.read((char *) &(*this.bmpinfoheader.x_pix_per_meter),sizeof(*this.bmpinfoheader.x_pix_per_meter));
  input.read((char *) &(*this.bmpinfoheader.y_pix_per_meter),sizeof(*this.bmpinfoheader.y_pix_per_meter));
  input.read((char *) &(*this.bmpinfoheader.colors_used),sizeof(*this.bmpinfoheader.colors_used));
  input.read((char *) &(*this.bmpinfoheader.color_important),sizeof(*this.bmpinfoheader.color_important));

  //Reviso si tiene paleta de colores:
  if ((*this.bmpinfoheader.bit_count) == 32) {
    input.read((char *) &(*this.rgb.red_mask),sizeof(*this.rgb.red_mask));
    input.read((char *) &(*this.rgb.green_mask),sizeof(*this.rgb.green_mask));
    input.read((char *) &(*this.rgb.blue_mask),sizeof(*this.rgb.blue_mask));
    input.read((char *) &(*this.rgb.alpha_mask),sizeof(*this.rgb.alpha_mask));
    input.read((char *) &(*this.rgb.color_space_type),sizeof(*this.rgb.color_space_type));
    input.read((char *) &(*this.rgb.unused),sizeof(*this.rgb.unused));
  }
}
