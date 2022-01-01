#pragma once
#include "glm/glm.hpp"
#include "TetrisColor.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include "VertexArrayBuffer.h"
#include "ElementArrayBuffer.h"

namespace Tetris {

class Brick
{
public:
  Brick(Color color);
  Brick(const std::string& texture_fn, Color color);
  Brick(Brick&& other) noexcept;
  Brick(Brick&) = delete;
  ~Brick() = default;

  void Bind() const;
  glm::vec2 Position() const;
  void Translate(const glm::vec2 vec);
  void SetPosition(const glm::vec2 position);
private:
  void Init(Color color);

  glm::vec2 pos_{ 0, 0 };
  VertexArray vao_;
  VertexArrayBuffer vbo_;
  ElementArrayBuffer ebo_;
  Color color_{Color::RED};
  Texture2D texture_;
};

}


