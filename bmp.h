#ifndef _BMP_H_
#define _BMP_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>
#include <cstdint>

using namespace std;

// ESTRUCTURAS PARA EL HEADER DEL BMP
//#pragma pack(2)
typedef struct {
    uint16_t bfType; // magic numbre for File
    uint32_t bfSize; // Size of File
    uint16_t bfReserved1; //Reserved
    uint16_t bfReserved2; //...
    uint32_t bfIffBits; // Offset to bitmap data
}bmpfileheader;

//#pragma pack()

typedef struct{
  uint32_t bit_size;
  int32_t bit_width;
  int32_t bit_height;
  uint16_t planes;
  uint16_t bit_count;
  uint32_t compression;
  uint32_t image_size;
  int32_t x_pix_per_meter;
  int32_t y_pix_per_meter;
  uint32_t colors_used;
  uint32_t color_important;
}bmpinfoheader;

typedef struct{
  uint32_t red_mask{0x00ff0000};
  uint32_t green_mask{0x0000ff00};
  uint32_t blue_mask{0x000000ff};
  uint32_t alpha_mask{0xff000000};
  uint32_t color_space_type{0x73524742};
  uint32_t unused[16]{0};
}rgb;

class bmp{
private:
    bmpfileheader bmpfileheader;
    bmpinfoheader bmpinfoheader;
    rgb rgb;
    std::vector<uint8_t> data;

public:
  bmp (const fstream);
  //bmp ();
  virtual ~bmp ();
};

#endif
