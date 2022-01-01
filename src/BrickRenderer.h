#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Brick.h"

namespace Tetris {

class Tetris;

class BrickRenderer
{
public:
  BrickRenderer() = delete;
  BrickRenderer(BrickRenderer&) = delete;

  static void Draw(const Brick& brick, const Shader& shader, glm::vec3 scale);
};

}


