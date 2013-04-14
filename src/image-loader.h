#ifndef EARTH_IMAGE_LOADER_H_
#define EARTH_IMAGE_LOADER_H_

namespace e {

class Image;

class ImageLoader {
 public:
  static Image* LoadPNG(const char* fname);
};

}

#endif

