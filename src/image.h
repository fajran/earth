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

