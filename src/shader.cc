#include "shader.h"

#include <assert.h>
#include <fstream>
#include <streambuf>
#include <iostream>

namespace e {

static std::string LoadFile(const std::string fname) {
  std::ifstream s(fname.c_str());
  std::string content((std::istreambuf_iterator<char>(s)),
                      std::istreambuf_iterator<char>());
  return content;
}

Shader::Shader(const std::string vertex_shader_file,
               const std::string fragment_shader_file)
    : vertex_shader_file_(vertex_shader_file),
      fragment_shader_file_(fragment_shader_file),
      program_(0) {
}

Shader::~Shader() {
  Unload();
}

void Shader::Load() {
  std::string vs = LoadFile(vertex_shader_file_);
  std::string fs = LoadFile(fragment_shader_file_);

  char const* src;
  GLint res = GL_FALSE;

  // compile and check vertex shader
  src = vs.c_str();
  GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vsId, 1, &src, NULL);
  glCompileShader(vsId);

  glGetShaderiv(vsId, GL_COMPILE_STATUS, &res);
  if (res != GL_TRUE) {
    int length;
    glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &length);
    char msg[length+1];
    glGetShaderInfoLog(vsId, length, NULL, msg);
    std::cerr << "Vertex shader error: " << msg << std::endl;
  }
  assert(res == GL_TRUE);

  // compile and check fragment shader
  src = fs.c_str();
  GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fsId, 1, &src, NULL);
  glCompileShader(fsId);

  glGetShaderiv(fsId, GL_COMPILE_STATUS, &res);
  if (res != GL_TRUE) {
    int length;
    glGetShaderiv(fsId, GL_INFO_LOG_LENGTH, &length);
    char msg[length+1];
    glGetShaderInfoLog(fsId, length, NULL, msg);
    std::cerr << "Fragment shader error: " << msg << std::endl;
  }
  assert(res == GL_TRUE);

  // create program
  GLuint programId = glCreateProgram();
  glAttachShader(programId, vsId);
  glAttachShader(programId, fsId);
  glLinkProgram(programId);

  glGetProgramiv(programId, GL_LINK_STATUS, &res);
  if (res != GL_TRUE) {
    int length;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
    char msg[length+1];
    glGetProgramInfoLog(programId, length, NULL, msg);
    std::cerr << "Program link error! " << msg << std::endl;
  }
  assert(res == GL_TRUE);

  glDeleteShader(vsId);
  glDeleteShader(fsId);

  program_ = programId;
}

void Shader::Unload() {
  if (program_ != 0) {
    glDeleteProgram(program_);
  }
}

GLuint Shader::GetUniformLocation(const std::string name) {
  return glGetUniformLocation(program_, name.c_str());
}

GLuint Shader::GetAttribLocation(const std::string name) {
  return glGetAttribLocation(program_, name.c_str());
}

}

