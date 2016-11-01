// image.h --- A class for managing digital images
//
// This file implements the longer member functions declared in class Image.
// See the header file image.h for more details.
//
// The image io routines currently make use of the FreeImage project, which is available at
// http://freeimage.sourceforge.net
// which was created by Floris van der Berg, and is currently being maintained by Herve Drolon.
//

// Created by Robert R. Snapp on 30 Aug 2016.

#include <FreeImage.h>
#include <iostream>
#include <fstream>
#include <string>
#include "image.h"

Image::Image(const std::string &path) {
  int fif_load_option = 0;
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
  fif = FreeImage_GetFileType(path.c_str(), 0);
  if (fif == FIF_UNKNOWN) {
    // try to guess the file format from the file extension.
    fif = FreeImage_GetFIFFromFilename(path.c_str());
  }
  if (fif == FIF_UNKNOWN) {
    // Give up. Bad input.
    throw std::runtime_error(std::string("Can't infer the format of the file ") + path);
  }

  // fif is known. Is it readable?
  if (! FreeImage_FIFSupportsReading(fif)) {
    throw std::runtime_error(std::string("Cannot read the file ") + path);
  }

  // fif is known and file is readable. Let's read it
      
  if (fif == FIF_JPEG) {
    fif_load_option = JPEG_EXIFROTATE;  // orient the image to match its metadata.
  }

  FIBITMAP *bitmap = FreeImage_Load(fif, path.c_str(), fif_load_option);
  if (! bitmap) {
    throw std::runtime_error(std::string("Can't create a bitmap from file ") + path);
  }

  rows = FreeImage_GetHeight(bitmap);
  cols = FreeImage_GetWidth(bitmap);
  bytes_per_row = FreeImage_GetLine(bitmap);
  bands = FreeImage_GetBPP(bitmap)/8;
  size = rows*bytes_per_row;

  // Some diagnostic information
  std::cout << "Found and read file " << path << "(" << rows << "*" << cols << ")" << std::endl;
  std::cout << "Number of bits per pixel = " << FreeImage_GetBPP(bitmap) << std::endl;
  std::cout << "Line width in bytes = " << bytes_per_row << std::endl;
  std::cout << "Pitch (width rounded to next 32 bit boundary) = "
            << FreeImage_GetPitch(bitmap) << std::endl;
  std::cout << "Red   mask = " << FreeImage_GetRedMask(bitmap)   << std::endl;
  std::cout << "Green mask = " << FreeImage_GetGreenMask(bitmap) << std::endl;
  std::cout << "Blue  mask = " << FreeImage_GetBlueMask(bitmap)  << std::endl;

  pixels = new unsigned char [size];
  if (! pixels) {
    std::runtime_error(std::string("Can't allocate a pixel buffer for file ") + path);
  }
    
  const unsigned int red_mask   = 0xFF0000;
  const unsigned int green_mask = 0x00FF00;
  const unsigned int blue_mask  = 0x0000FF;
  const int bits_per_pixel     = 24;

  FreeImage_ConvertToRawBits(pixels, bitmap, bytes_per_row, bits_per_pixel,
                             red_mask, green_mask, blue_mask, FALSE);

  // release the bitmap to avoid a memory leak.
  FreeImage_Unload(bitmap);
}


int Image::write_png(const std::string &path) {

  const unsigned int red_mask             = 0xFF0000;
  const unsigned int green_mask           = 0x00FF00;
  const unsigned int blue_mask            = 0x0000FF;
  const unsigned int bits_per_pixel       = 24;
  const bool top_left_pixel_appears_first = false;

  //  unsigned int bytes_per_row = 3 * cols;
  unsigned int output_bytes_per_row = 3 * cols;
  // Create a FITBITMAP data structure that contains the image data.
  
  FIBITMAP* fi_image = FreeImage_ConvertFromRawBits(pixels, cols, rows, output_bytes_per_row,
                                                    bits_per_pixel, red_mask, green_mask,
                                                    blue_mask, top_left_pixel_appears_first);

  // Save the image as PNG file.
  FreeImage_Save(FIF_PNG, fi_image, path.c_str(), 0);

  //
  FreeImage_Unload(fi_image);
  return rows*output_bytes_per_row;
}
    
