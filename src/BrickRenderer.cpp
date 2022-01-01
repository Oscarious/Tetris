#include "BrickRenderer.h"
#include "Brick.h"
#include "Tetris.h"
#include "common/GLHelper.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Tetris {

void BrickRenderer::Draw(const Brick& brick, const Shader &shader, glm::vec3 scale) {
  brick.Bind();
  glm::mat4 proj = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
  glm::mat4 model = glm::mat4(1);
  model = glm::scale(model, scale);
  model = glm::translate(model, glm::vec3(brick.Position(), 0.0f));

  shader.setMat4("projection", proj);
  shader.setMat4("model", model);

  GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

}

