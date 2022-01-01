#pragma once

namespace Tetris {

enum class Color { RED = 0, GREEN = 1, BLUE = 2, YELLOW = 3, PURPLE = 4, GRAY, PINK, BLACK, WHITE, last };

const float colors[static_cast<int>(Color::last)][3] = {
  0.9f, 0.3f, 0.3f, // RED
  0.4f, 0.7f, 0.5f, // GREEN
  0.3f, 0.5f, 0.9f, // BLUE
  0.9f, 0.8f, 0.3f, // YELLOW
  0.7f, 0.3f, 0.9f, // PURPLE
  0.8f, 0.8f, 0.8f, // GRAY
  0.9f, 0.87f, 0.75f, // PINK
  0.0f, 0.0f, 0.0f, // BLACK
  1.0f, 1.0f, 1.0f  // WHITE
};

}