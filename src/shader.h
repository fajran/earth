#ifndef EARTH_SHADER_H_
#define EARTH_SHADER_H_

#include <string>

#include <GL/glew.h>

namespace e {

class Shader {
 public:
  Shader(const std::string vertex_shader_file,
         const std::string fragment_shader_file);
  virtual ~Shader();

  void Load();
  void Unload();

  GLuint program() { return program_; }

  GLuint GetUniformLocation(const std::string name);
  GLuint GetAttribLocation(const std::string name);

 private:
  const std::string vertex_shader_file_;
  const std::string fragment_shader_file_;

  GLuint program_;
};

}

#endif

