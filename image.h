// image.h --- A class for managing digital images
//
// Creates class Image that can operate on jpg and png images.
// Functions are for
//   * reading jpg and png images from a file.
//   * creating a new blank image.
//   * reading arbitrary pixel values from the image.
//   * modifiying any pixel value in the image.
//   * writing the image to a png file.
//
// The header also defines byte as a synomym for unsigned char.
//
// Some of the funtions are implemented in image.cc
//
// Created by Robert R. Snapp on 30 Aug 2016.

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

//using byte = unsigned char;

class Image {
  int rows;
  int cols;
  int bands;  // should be 1 for a graylevel image, 3 for an RGB image, 4 for an RGBA image.
  int bytes_per_row;
  int size;
  unsigned char *pixels;

public:

  // Here is a "concrete" constructor for the image class.
  Image(int r, int c, int b=3) : rows(r), cols(c), bands(b) {
    bytes_per_row = cols*bands;
    size = rows*bytes_per_row;
    pixels = new unsigned char [size];
    for (int i = 0; i < size; i++) {
      pixels[i] = 0x00;
    }
  }

  // The following constructor creates an image object from data stored in a jpeg or png image.
  // The calling program must provide the path of the file.
  Image(const std::string &path);
  
  // This is a copy constructor, which performs a "deep" copy of the pixel values.
  Image(const Image& im) : rows(im.rows), cols(im.cols), bands(im.bands),
                           bytes_per_row(im.bytes_per_row), size(im.size) {
    pixels = new unsigned char [size];
    for (int i = 0; i < size; i++) {
      pixels[i] = im.pixels[i];
    }
  }

  // This is a copy assignment constructor, which uses a cool trick from Stroustrup's book
  // "The C++ Programming Language", 4th edition, page 508.
  /*Image& operator=(const Image& im) {
    Image tmp = new Image(im);        // Make a local copy of the image (using the copy constructor above)
    std::swap(tmp, *this); // swap the member data.
    return *this;
  }*/

  int getRows() {return rows;}
  int getCols() {return cols;}
  int getBands() {return bands;}
  
  unsigned char getPixel(int i, int j, int b=0) {
    int offset = bytes_per_row*i + j*bands + b;
    return pixels[offset];
  }

  void putPixel(int i, int j, int b, unsigned char value) {
    int offset = bytes_per_row*i + j*bands + b;
    pixels[offset] = value;
  }
  
  int write_png(const std::string &path);
  
  ~Image() {
    delete [] pixels;
  }
};
    
