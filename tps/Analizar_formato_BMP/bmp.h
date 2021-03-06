#ifndef _BMP_H_
#define _BMP_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <stdexcept>
#include <ctime>
#include <cstdint>
#include <vector>
#include <cmath>

using namespace std;
// ESTRUCTURAS PARA EL HEADER DEL BMP
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{ 0x4D42 };          // File type always BMP which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size{ 0 };               // Size of the file (in bytes)
    uint16_t reserved1{ 0 };               // Reserved, always 0
    uint16_t reserved2{ 0 };               // Reserved, always 0
    uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)
};

struct BMPInfoHeader {
    uint32_t size{ 0 };                      // Size of this header (in bytes)
    int32_t width{ 0 };                      // width of bitmap in pixels
    int32_t height{ 0 };                     // width of bitmap in pixels
                                             //       (if positive, bottom-up, with origin in lower left corner)
                                             //       (if negative, top-down, with origin in upper left corner)
    uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
    uint16_t bit_count{ 0 };                 // No. of bits per pixel
    uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t size_image{ 0 };                // 0 - for uncompressed images
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    uint32_t colors_important{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required

};

struct BMPColorHeader {
    uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
    uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
    uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
    uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
    uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
    uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};
#pragma pack(pop)

class bmp{
private:
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;
    BMPColorHeader bmp_color_header;
    vector<uint8_t> data;
    //vector<vector<uint8_t>> dataR;
    //vector<vector<uint8_t>> dataB;
    //vector<vector<uint8_t>> dataG;
    uint32_t row_stride { 0 };

public:
    bmp (fstream &);
    ~bmp ();
    bmp(int32_t, int32_t, bool);

    //Lectura:
    void read(fstream &);
    //Escritura:
    void write(fstream &);

    void setHeight( int32_t &);
    void setWidth( int32_t &);
    void setXperPixel(int32_t & xx){bmp_info_header.x_pixels_per_meter=xx;}
    void setYperPixel(int32_t & yy){bmp_info_header.y_pixels_per_meter=yy;}
    void setSize(uint32_t & x){bmp_info_header.size=x;}
    void setSizeImage(uint32_t & x){
      bmp_info_header.size_image=x;
      (*this).data.resize(x);}


    BMPFileHeader getFileHeader() {return (*this).file_header;}
    BMPInfoHeader getInfoHeader() {return (*this).bmp_info_header;}
    BMPColorHeader getColorHeader() {return (*this).bmp_color_header;}
    vector<uint8_t> getData() {return (*this).data;}
    //int getDataSize() {return (*this).data.size();}
    //uint16_t getBitCount() {return (*this).bmp_info_header.bit_count;}


    void checkColorHeader();

    uint32_t make_stride_aligned(uint32_t);

    void readFileHeader(fstream &);
    void readInfoHeader(fstream &);
    void readColorHeader(fstream & );
    void readData(fstream &);

    void writeFileHeader(fstream &);
    void writeInfoHeader(fstream &);
    void writeColorHeader(fstream &);
    void writeData(fstream &);
    void write_headers_and_data(fstream &);

    void copyData(bmp &);
    void copyData2(bmp &);
    void grayScale();
    void grayScale2();
    void negative();
    void write(const char *);

    //friend ostream & operator<<(ostream &,bmp &);
    //friend ostream & operator<<(ostream &,BMPInfoHeader );
    //friend ostream & operator<<(ostream &,BMPFileHeader );
    //friend ostream & operator<<(ostream &,BMPColorHeader );
    //friend ostream & operator<<(ostream &,vector<uint8_t> );


    void fill_region(uint32_t , uint32_t , uint32_t , uint32_t , uint8_t , uint8_t , uint8_t , uint8_t );

};
#endif
