#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>
#include <cstdint>

#include "cmdline.h"
#include "options.h"
#include "bmp.h"
#include "BmpHeader.h"

// ESTRUCTURAS PARA EL HEADER DEL BMP
#pragma pack(2)
typedef struct {
    unsigned short bfType; // magic numbre for File
    unsigned int bfSize; // Size of File
    unsigned short bfReserved1; //Reserved
    unsigned short bfReserved2; //...
    unsigned int bfIffBits; // Offset to bitmap data
}bmpfileheader;

#pragma pack()

typedef struct{
  unsigned int biSize;
  int biWidth;
  int biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  int biXPelsPerMeter;
  int biYPelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
}bmpinfoheader;

typedef struct{
  unsigned char rgbBlue;
  unsigned char rgbRed;
  unsigned char rgbGreen;
  unsigned char rgbReserved;
}rgb;

class bmp :public format{
private:
    bmpfileheader bmpfileheader;
    bmpinfoheader bmpinfoheader;
    rgb rgb;

public:
  bmp (fstream);
  virtual ~bmp ();
};
