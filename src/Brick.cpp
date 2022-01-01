#include "Brick.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "TetrisConstants.h"

namespace Tetris {

// Pure color Brick
Brick::Brick(Color color) : color_(color) {
  Init(color);
}

Brick::Brick(const std::string& texture_fn, Color color)
  : color_(color), texture_(Texture2D(texture_fn)) {
  Init(color);
}

Brick::Brick(Brick&& other) noexcept : 
  texture_(std::move(other.texture_))
{
  pos_ = other.pos_;
  vao_ = other.vao_;
  vbo_ = other.vbo_;
  ebo_ = other.ebo_;
  color_ = other.color_;
}

void Brick::Bind() const {
  vao_.Bind();
  texture_.Bind();
}

glm::vec2 Brick::Position() const
{
  return pos_;
}

void Brick::Translate(const glm::vec2 vec)
{
  pos_ += vec;
}

void Brick::SetPosition(const glm::vec2 position) {
  pos_ = position;
}

void Brick::Init(Color color) {
  const int color_index = static_cast<int>(color);
  float vertices[] = {
     0.0f,  0.0f, colors[color_index][0], colors[color_index][1], colors[color_index][2], 0.0f, 0.0f,
     BRICK_SIZE, 0.0f, colors[color_index][0], colors[color_index][1], colors[color_index][2], 1.0f, 0.0f,
     BRICK_SIZE, BRICK_SIZE, colors[color_index][0], colors[color_index][1], colors[color_index][2], 1.0f, 1.0f,
      0.0f,  BRICK_SIZE, colors[color_index][0], colors[color_index][1], colors[color_index][2], 0.0f, 1.0f,
  };

  unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
  vbo_.Init(vertices, sizeof(vertices), 4);
  vbo_.AssignAttribPointer(0, 3, 7 * sizeof(float), (void*)0);
  vbo_.AssignAttribPointer(1, 3, 7 * sizeof(float), (void*)(2 * sizeof(float)));
  vbo_.AssignAttribPointer(2, 2, 7 * sizeof(float), (void*)(5 * sizeof(float)));
  ebo_.Init(indices, sizeof(indices), 6);
}

}