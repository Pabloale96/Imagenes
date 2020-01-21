#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "bmp.h"

using namespace std;

//Funciones:
uint32_t bmp::make_stride_aligned(uint32_t align_stride) {
    uint32_t new_stride = (*this).row_stride;
    while (new_stride % align_stride != 0) {
        new_stride++;
    }
    return new_stride;
}

// Metodos de la clase de bmp:

//BMPFileHeader & getFileHeader() {return (*this).file_header;}

// Constructores:
bmp::bmp( fstream & image){
  (*this).read(image);
}

bmp::bmp(int32_t width, int32_t height, bool has_alpha) {
    if (width <= 0 || height <= 0) {
        throw  runtime_error("The image width and height must be positive numbers.");
    }

    bmp_info_header.width = width;
    bmp_info_header.height = height;
    if (has_alpha) {
        bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);

        bmp_info_header.bit_count = 32;
        bmp_info_header.compression = 3;
        (*this).row_stride = width * 4;
        data.resize((*this).row_stride * height);
        for (size_t i = 0; i < data.size(); i++) {
          data[0]=0;
        }
        file_header.file_size = file_header.offset_data + data.size();
    }
    else {
        bmp_info_header.size = sizeof(BMPInfoHeader);
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

        bmp_info_header.bit_count = 24;
        bmp_info_header.compression = 0;
        (*this).row_stride = width * 3;
        data.resize((*this).row_stride * height);
        for (size_t i = 0; i < data.size(); i++) {
          data[0]=0;
        }

        uint32_t new_stride = (*this).make_stride_aligned(4);
        file_header.file_size = file_header.offset_data + static_cast<uint32_t>(data.size()) + bmp_info_header.height * (new_stride - (*this).row_stride);
    }
}
bmp::~bmp(){}

// Lectura:
void bmp::read( fstream & image){
  (*this).readFileHeader(image);
  (*this).readInfoHeader(image);
  // Salto a la parte de data:
  image.seekg((*this).file_header.offset_data, image.beg);
  (*this).readData(image);

}
void bmp::readData( fstream & image){
  // Adjust the header fields for output.
  // Some editors will put extra info in the image file, we only save the headers and the data.
  if(bmp_info_header.bit_count == 32) {
      bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
      file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
  } else {
      bmp_info_header.size = sizeof(BMPInfoHeader);
      file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
  }
  file_header.file_size = file_header.offset_data;
  if (bmp_info_header.height < 0) {
      throw  runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
  }

  data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

  // Here we check if we need to take into account row padding
  if (bmp_info_header.width % 4 == 0) {
      image.read((char*)data.data(), data.size());
      file_header.file_size += static_cast<uint32_t>(data.size());
  }
  else {
      (*this).row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
      uint32_t new_stride = (*this).make_stride_aligned(4);
      vector<uint8_t> padding_row(new_stride - (*this).row_stride);

      for (int y = 0; y < bmp_info_header.height; ++y) {
          image.read((char*)(data.data() + (*this).row_stride * y), (*this).row_stride);
          image.read((char*)padding_row.data(), padding_row.size());
      }
      file_header.file_size += static_cast<uint32_t>(data.size()) + bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
  }
}

void bmp::readFileHeader( fstream & image){
  image.read((char *) &((*this).file_header), sizeof(file_header));
  if (file_header.file_type != 0x4D42){
    throw runtime_error ("Error! No se reconoce el formato.");
  }
}
void bmp::readInfoHeader( fstream & image){
  image.read((char *) &((*this).bmp_info_header),sizeof(bmp_info_header));
  if(bmp_info_header.bit_count == 32) {
    // Check if the file has bit mask color information
    if(bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
        (*this).readInfoHeader(image);
    } else {
        cout << "Error! el archivo no tiene una bit mask." << '\n';
        throw runtime_error("Error! No se reconoce el formato.");
    }
  }
}

void bmp::readColorHeader( fstream & image){
  image.read((char*)&bmp_color_header, sizeof(bmp_color_header));
  // Check if the pixel data is stored as BGRA and if the color space type is sRGB
  (*this).checkColorHeader();
}
void bmp::checkColorHeader(){
  BMPColorHeader expected_color_header;
  if(expected_color_header.red_mask != bmp_color_header.red_mask ||
      expected_color_header.blue_mask != bmp_color_header.blue_mask ||
      expected_color_header.green_mask != bmp_color_header.green_mask ||
      expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {
      throw  runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
  }
  if(expected_color_header.color_space_type != bmp_color_header.color_space_type) {
      throw  runtime_error("Unexpected color space type! The program expects sRGB values");
  }
}


//Escritura:

void bmp::write( fstream & of){
  if (bmp_info_header.bit_count == 32) {
      write_headers_and_data(of);
  }
  else if (bmp_info_header.bit_count == 24) {
      if (bmp_info_header.width % 4 == 0) {
          write_headers_and_data(of);
      }
      else {
          uint32_t new_stride = (*this).make_stride_aligned(4);
          vector<uint8_t> padding_row(new_stride - (*this).row_stride);

          (*this).writeFileHeader(of);
          (*this).writeInfoHeader(of);
          (*this).writeColorHeader(of);

          for (int y = 0; y < bmp_info_header.height; ++y) {
              of.write((const char*)(data.data() + (*this).row_stride * y), (*this).row_stride);
              of.write((const char*)padding_row.data(), padding_row.size());
          }
      }
  }
  else {
      throw runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
  }
}
void bmp::writeFileHeader( fstream & of){
  of.write((const char*)&file_header, sizeof(file_header));
}
void bmp::writeInfoHeader( fstream & of){
  of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
}

void bmp::writeColorHeader( fstream & of){
  if(bmp_info_header.bit_count == 32) {
      of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));
  }
}

void bmp::writeData( fstream & of){
  of.write((const char*)data.data(), data.size());
}
void bmp::write_headers_and_data( fstream & of){
  (*this).writeFileHeader(of);
  (*this).writeInfoHeader(of);
  (*this).writeColorHeader(of);
  (*this).writeData(of);
}

void bmp::copyData(bmp & bmpAux){

  //(*this).bmp_info_header.x_pixels_per_meter=(*this).bmp_info_header.width/bmpAux.bmp_info_header.width;
  //(*this).bmp_info_header.y_pixels_per_meter=(*this).bmp_info_header.height/bmpAux.bmp_info_header.height;

  size_t j = 0;
  while(j < (*this).data.size()) {
    for (size_t i = 0; i < bmpAux.data.size(); i++) {
      (*this).data[j] = bmpAux.data[i];
      j++;
      if (j ==(*this).data.size()) {
        break;
      }
    }
  //}
}
}

void bmp::write(const char *fname) {
    fstream of{ fname, ios_base::binary };
    of.open(fname, ios::binary|ios::out);
    if (of) {
        if (bmp_info_header.bit_count == 32) {
            write_headers_and_data(of);
        }
        else if (bmp_info_header.bit_count == 24) {
            if (bmp_info_header.width % 4 == 0) {
                write_headers_and_data(of);
            }
            else {
                uint32_t new_stride = make_stride_aligned(4);
                vector<uint8_t> padding_row(new_stride - (*this).row_stride);

                (*this).writeFileHeader(of);
                (*this).writeInfoHeader(of);
                (*this).writeColorHeader(of);

                for (int y = 0; y < bmp_info_header.height; ++y) {
                    of.write((const char*)(data.data() + (*this).row_stride * y), (*this).row_stride);
                    of.write((const char*)padding_row.data(), padding_row.size());
                }
            }
        }
        else {
            throw runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
        }
    }
    else {
        throw runtime_error("Unable to open the output image file.");
    }
    (of).close();
}

void bmp::fill_region(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint8_t B, uint8_t G, uint8_t R, uint8_t A) {
    if (x0 + w > (uint32_t)bmp_info_header.width || y0 + h > (uint32_t)bmp_info_header.height) {
        throw std::runtime_error("The region does not fit in the image!");
    }

    uint32_t channels = bmp_info_header.bit_count / 8;
    for (uint32_t y = y0; y < y0 + h; ++y) {
        for (uint32_t x = x0; x < x0 + w; ++x) {
            data[channels * (y * bmp_info_header.width + x) + 0] = B;
            data[channels * (y * bmp_info_header.width + x) + 1] = G;
            data[channels * (y * bmp_info_header.width + x) + 2] = R;
            if (channels == 4) {
                data[channels * (y * bmp_info_header.width + x) + 3] = A;
            }
        }
    }
}

void bmp::setHeight(int32_t & h) {
  bmp_info_header.height=h;
  (*this).row_stride = bmp_info_header.width * 3;
  data.resize((*this).row_stride * bmp_info_header.height);}
void bmp::setWidth(int32_t & w) {
  bmp_info_header.width=w;
  (*this).row_stride = bmp_info_header.width * 3;
  data.resize((*this).row_stride * bmp_info_header.height);}
