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

#include "node-visitor.h"

#include "node.h"

namespace e {

NodeVisitor::NodeVisitor() {
}

NodeVisitor::~NodeVisitor() {
}

void NodeVisitor::Update(Node* root) {
  root->Update();
  glm::mat4 matrix = root->Matrix();

  std::vector<Node*> children = root->children();
  for (auto it=children.begin(); it != children.end(); ++it) {
    Node* child = *it;
    child->Apply(matrix);
    Update(child);
  }
}

void NodeVisitor::Draw(Node* root) {
  root->Draw();

  std::vector<Node*> children = root->children();
  for (auto it=children.begin(); it != children.end(); ++it) {
    Node* child = *it;
    Draw(child);
  }
}

}

