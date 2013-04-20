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

#ifndef EARTH_IMAGE_H_
#define EARTH_IMAGE_H_

namespace e {

class Image {
 public:
  Image(const unsigned int width, const unsigned int height,
        const unsigned int channels, const unsigned int depth,
        const unsigned char* data)
      : width_(width), height_(height), channels_(channels), depth_(depth),
        data_(data) {
  }

  virtual ~Image() {
    delete data_;
    data_ = 0;
  }

  const unsigned int width() { return width_; }
  const unsigned int height() { return height_; }
  const unsigned int channels() { return channels_; }
  const unsigned int depth() { return depth_; }
  const unsigned char* data() { return data_; }

 private:
  const unsigned int width_;
  const unsigned int height_;
  const unsigned int channels_;
  const unsigned int depth_;
  const unsigned char* data_;
};

};

#endif

