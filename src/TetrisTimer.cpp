#include "TetrisTimer.h"
#include <iostream>

namespace Tetris {

TetrisTimer::TetrisTimer(std::chrono::milliseconds count_down)
  : count_down_(count_down)
{}

void TetrisTimer::CheckAndFire(const std::function<void(Tetris& tetris)>& callback, Tetris& tetris, bool repeat)
{
  std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
  std::chrono::milliseconds dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
  if (count_down_ <= dt) {
    callback(tetris);
    if (repeat) {
      start = std::chrono::system_clock::now();
    }
  }
}

}