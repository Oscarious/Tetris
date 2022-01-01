#pragma once
#include <functional>
#include <chrono>
#include "Tetris.h"

namespace Tetris {

class TetrisTimer
{
  /**
   * Should instance one first and call 'CheckAndFire' inside a event loop
   * 
   */
  
public:
  TetrisTimer(std::chrono::milliseconds ms);

  void CheckAndFire(const std::function<void(Tetris&)>& callback, Tetris& tetris, bool repeat);
private:
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  std::chrono::milliseconds count_down_;
};

}


