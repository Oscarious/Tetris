#pragma once
#include "VertexArray.h"
#include "VertexArrayBuffer.h"
#include "ElementArrayBuffer.h"
#include "Tetris.h"
#include "Shader.h"
#include "TetrisConstants.h"

namespace Tetris {

class GameBoard
{
public:
  GameBoard(const std::string& bg_fn, const std::string& brick_fn);
  void Render(glm::vec2 position, Shader& shader);
  bool Collide(Tetris& tetris, glm::vec2 transaltion);
  bool GameOver();
private:
  void ClearBricks();
  glm::vec2 pos_{0.0f, 0.0f};
  Brick board_, brick_;
  bool bricks_[TETRIS_HEIGHT][TETRIS_WIDTH] = { false };
};

}

