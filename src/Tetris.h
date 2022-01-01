#pragma once
#include <array>
#include <vector>
#include "glm/glm.hpp"
#include "TetrisShape.h"
#include "BrickRenderer.h"
#include "TetrisConstants.h"

namespace Tetris {

class Tetris
{
friend class GameBoard;

public:
  Tetris(const std::string& texture_fn, Color color);
  Tetris(Tetris&) = delete;
  void Render(const Shader& shader, glm::vec3 scale);
  void Translate(const glm::vec2& translation);
  void SetPosition(const glm::vec2& position);
  void SetShape(TetrisShape shape);
  void Rotate();
  // coordinate  = pos_ / BRICK_SIZE
  glm::i8vec4 CoordinateBoundaries();

private:
  struct Boundary {
    int left, top, right, bottom;
  } bound_;
  glm::vec2 pos_{ 3*BRICK_SIZE, 0 };
  Brick brick_;
  TetrisShape shape_;
  std::array<std::array<bool, 4>, 4>  brick_matrix_;
};

}

 
