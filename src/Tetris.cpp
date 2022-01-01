#include "Tetris.h"
#include "TetrisConstants.h"
#include <iostream>

namespace {

void RotateMatrix(std::array<std::array<bool, 4>, 4>& matrix, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = i; j < size; ++j) {
      std::swap(matrix[i][j], matrix[j][i]);
    }
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size / 2; ++j) {
      std::swap(matrix[i][j], matrix[i][size - j - 1]);
    }
  }
}

const int BOUND_MAX = 1000;
const int BOUND_MIN = -1000;
}

namespace Tetris {

Tetris::Tetris(const std::string& texture_fn, Color color)
  : brick_(Brick(texture_fn, color))
{
  SetShape(static_cast<TetrisShape>(rand() % static_cast<int>(TetrisShape::last)));
}

void Tetris::Render(const Shader& shader, glm::vec3 scale)
{
  // to move bricks to the left-top corner, we now use the offset to do that.
  int top_offset = bound_.top;
  int left_offset = bound_.left;
  for (int i = 0; i < brick_matrix_.size(); ++i) {
    for (int j = 0; j < brick_matrix_[i].size(); ++j) {
      if (brick_matrix_[i][j]) {
        brick_.SetPosition({ pos_.x + (j - left_offset) * BRICK_SIZE, pos_.y + (i - top_offset) * BRICK_SIZE });
        BrickRenderer::Draw(brick_, shader, scale);
      }
    }
  }
}

void Tetris::SetPosition(const glm::vec2& position)
{
  pos_ = position;
}

void Tetris::SetShape(TetrisShape shape)
{
  shape_ = shape;
  switch (shape) {
  case TetrisShape::STICK:
    brick_matrix_ = {
      {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
      }
    };
    bound_ = { 0, 0, 0, 3 };
    break;
  case TetrisShape::BLOCK:
    brick_matrix_ = {
      {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      }
    };
    bound_ = { 0, 0, 1, 1 };
    break;
  case TetrisShape::RLSHAPE:
    brick_matrix_ = {
      {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
      }
    };
    bound_ = { 0, 0, 1, 2 };
    break;
  case TetrisShape::LSHAPE:
    brick_matrix_ = {
      {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
      }
    };
    bound_ = { 0, 0, 1, 2 };
    break;
  case TetrisShape::TSHAPE:
    brick_matrix_ = {
      {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      }
    };
    bound_ = { 0, 0, 2, 1 };
    break;
  case TetrisShape::ZSHAPE:
  default:
    brick_matrix_ = {
      {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      }
    };
    bound_ = { 0, 0, 2, 1 };
    break;
  };
}

void Tetris::Rotate()
{
  if (pos_.x + bound_.left * BRICK_SIZE < 0 || pos_.x + bound_.right * BRICK_SIZE >= TETRIS_WIDTH * BRICK_SIZE) return;
  if (pos_.y + bound_.top * BRICK_SIZE < 0 || pos_.y + bound_.bottom * BRICK_SIZE >= TETRIS_HEIGHT * BRICK_SIZE) return;
  if (shape_ == TetrisShape::STICK) {
    RotateMatrix(brick_matrix_, 4);
  } else {
    RotateMatrix(brick_matrix_, 3);
  }
  bound_.top = BOUND_MAX;
  bound_.left = BOUND_MAX;
  bound_.bottom = BOUND_MIN;
  bound_.right = BOUND_MIN;
  for (int i = 0; i < brick_matrix_.size(); ++i) {
    for (int j = 0; j < brick_matrix_.size(); ++j) {
      if (brick_matrix_[i][j]) {
        bound_.top = std::min(bound_.top, i);
        bound_.left = std::min(bound_.left, j);
        bound_.bottom = std::max(bound_.bottom, i);
        bound_.right = std::max(bound_.right, j);
      }
    }
  }
}

glm::i8vec4 Tetris::CoordinateBoundaries()
{
  glm::i8vec2 cur_coord = pos_ / BRICK_SIZE;
  return glm::i8vec4{ cur_coord.x + bound_.left, cur_coord.y + bound_.top, cur_coord.x + bound_.right, cur_coord.y + bound_.bottom };
}

void Tetris::Tetris::Translate(const glm::vec2& translation)
{
  int top_offset = bound_.top;
  int left_offset = bound_.left;
  glm::vec2 tmp_pos = (pos_ + translation) / BRICK_SIZE;
  if (tmp_pos.x + bound_.left < 0 || tmp_pos.x + bound_.right - left_offset >= TETRIS_WIDTH) return;
  if (tmp_pos.y  + bound_.top < 0 || tmp_pos.y + bound_.bottom - top_offset >= TETRIS_HEIGHT) return;
  pos_ += translation;
}

}
