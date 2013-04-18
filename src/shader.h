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

