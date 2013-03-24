#ifndef EARTH_EARTH_H_
#define EARTH_EARTH_H_

namespace e {

class Earth {
 public:
  Earth();
  virtual ~Earth();

  void Init();
  void Update();
  void Render();
};

}

#endif

