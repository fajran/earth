// Copyright (C) 2013  Fajran Iman Rusadi
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "image-loader.h"

#include <stdio.h>
#include <assert.h>

#include <png.h>

#include "image.h"

namespace e {

// Source: http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
// Licensed under Creative Commons Attribution/Share-Alike License
Image* ImageLoader::LoadPNG(const char* fname) {
  FILE* f = fopen(fname, "rb");
  if (!f) {
    return NULL;
  }

  png_byte header[8];
  fread(header, 1, 8, f);

  int is_png = !png_sig_cmp(header, 0, 8);
  if (!is_png) {
    fclose(f);
    return NULL;
  }

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                               NULL, NULL, NULL);
  if (!png_ptr) {
    fclose(f);
    return NULL;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    fclose(f);
    return NULL;
  }

  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(f);
    return NULL;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(f);
    return NULL;
  }

  png_init_io(png_ptr, f);
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  int bit_depth, color_type;
  png_uint_32 width, height;

  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
               NULL, NULL, NULL);
  png_read_update_info(png_ptr, info_ptr);
  assert(color_type == 6); // only support/expect RGBA for the moment

  int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  png_byte* image_data = new png_byte[rowbytes * height];
  if (!image_data) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(f);
    return NULL;
  }

  png_bytep* row_pointers = new png_bytep[height];
  if (!row_pointers) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    fclose(f);
    return NULL;
  }

  for (int i=0; i<height; i++) {
    row_pointers[height - 1 - i] = image_data + i * rowbytes;
  }

  png_read_image(png_ptr, row_pointers);

  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  delete[] row_pointers;
  fclose(f);

  Image* image = new Image(width, height, 4 /* FIXME channel */, bit_depth,
                           image_data);
  return image;
}

}

