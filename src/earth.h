#ifndef EARTH_H_
#define EARTH_H_

namespace e {

class Earth {
 public:
  Earth();
  virtual ~Earth();

  void update();
  void render();
};

}

#endif

