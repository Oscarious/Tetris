#include "GameBoard.h"
#include "TetrisConstants.h"
#include "BrickRenderer.h"
#include <iostream>

namespace {
  int smallest_row_num = 2 * Tetris::TETRIS_HEIGHT;
}

namespace Tetris {

GameBoard::GameBoard(const std::string& bg_fn, const std::string& brick_fn)
  : board_(Brick(bg_fn, Color::PINK)), brick_(Brick(brick_fn, Color::WHITE)) {}

void GameBoard::Render(glm::vec2 position, Shader& shader)
{
  board_.SetPosition(position);
  BrickRenderer::Draw(board_, shader, {SCALE * 10.0f, SCALE * 20.0f, 0.0f});
  for (int i = 0; i < TETRIS_HEIGHT; ++i) {
    for (int j = 0; j < TETRIS_WIDTH; ++j) {
      if (bricks_[i][j]) {
        brick_.SetPosition({ pos_.x + j * BRICK_SIZE, pos_.y + i * BRICK_SIZE });
        BrickRenderer::Draw(brick_, shader, {SCALE, SCALE, 0.0F});
      }
    }
  }
}

bool GameBoard::GameOver() {
  for (int i = 0; i < TETRIS_WIDTH; ++i) {
    if (bricks_[0][i]) return true;
  }
  return false;
}

bool GameBoard::Collide(Tetris& tetris, glm::vec2 coord_transaltion)
{
  auto bounds = tetris.CoordinateBoundaries();
  //int left = bounds.x, top = bounds.y, right = bounds.z, bottom = bounds.w;
  int n = tetris.brick_matrix_.size();
  glm::vec2 cur_coord = tetris.pos_ / BRICK_SIZE;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < n; ++j) {
      if (tetris.brick_matrix_[i][j]) {
        glm::vec2 brick_coord = cur_coord + glm::vec2(j - tetris.bound_.left, i - tetris.bound_.top);
        glm::vec2 next_coord = brick_coord + coord_transaltion;
        // down collision
        if (brick_coord.y >= TETRIS_HEIGHT - 1 || bricks_[(int)brick_coord.y + 1][(int)brick_coord.x]) {
          // stabilize the tetris
          for (int p = 0; p < n; ++p) {
            for (int q = 0; q < n; ++q) {
              if (tetris.brick_matrix_[p][q]) {
                glm::vec2 coord_on_board = cur_coord + glm::vec2(q - tetris.bound_.left, p - tetris.bound_.top);
                bricks_[(int)coord_on_board.y][(int)coord_on_board.x] = true;
                smallest_row_num = std::min(smallest_row_num, (int)coord_on_board.y);
              }
            }
          }
          ClearBricks();
          // Move Tetris To the start point
          tetris.SetPosition({ 3.0f * BRICK_SIZE, 0.0f });
          tetris.SetShape(static_cast<TetrisShape>(rand() % static_cast<int>(TetrisShape::last)));
          return true;
        } else if (bricks_[(int)next_coord.y][(int)next_coord.x]) {
          return true;
        }
      }
    }
  }
  return false;
}

void GameBoard::ClearBricks()
{
  std::vector<int> cleared_rows{ smallest_row_num };
  for (int i = 0; i < TETRIS_HEIGHT; ++i) {
    for (int j = 0; j < TETRIS_WIDTH; ++j) {
      if (!bricks_[i][j]) break;
      if (j == TETRIS_WIDTH - 1) {
        cleared_rows.push_back(i);
      }
    }
  }
  int move_rows{};
  for (int i = cleared_rows.size() - 1; i > 0; --i) {
    int row = cleared_rows[i] - 1;
    ++move_rows;
    for (int j = row; j >= cleared_rows[i - 1]; --j) {
      memcpy(bricks_[j + move_rows], bricks_[j], sizeof(bricks_[j]));
    }
  }
  for (int i = 0; i < move_rows; ++i) {
    memset(bricks_[i + smallest_row_num], false, sizeof(bricks_[i + smallest_row_num]));
  }
}

}

