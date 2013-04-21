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

#ifndef EARTH_NODE_H_
#define EARTH_NODE_H_

#include <vector>
#include <glm/glm.hpp>

namespace e {

class Node {
 public:
  virtual ~Node();

  virtual void Apply(glm::mat4 matrix) = 0;

  virtual void Update() = 0;

  virtual glm::mat4 Matrix() = 0;

  virtual void Draw() = 0;

  std::vector<Node*> children() {
    return children_;
  }

  int total_children() {
    return children_.size();
  }

  Node* parent() { return parent_; }
  void set_parent(Node* node) { parent_ = node; }

  void AddChild(Node* child);
  void RemoveChild(Node* child);

 private:
  Node* parent_;
  std::vector<Node*> children_;
};

}

#endif

