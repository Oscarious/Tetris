#include <iostream>
#include "BrickRenderer.h"
#include <GLFW/glfw3.h>
//#include "glm/gtc//matrix_transform.hpp"
#include "common/GLHelper.h"
#include "Texture2D.h"
#include "Brick.h"
#include "Tetris.h"
#include "TetrisConstants.h"
#include "GameBoard.h"
#include "TetrisTimer.h"

namespace {

glm::vec2 translation;
bool rotation = false;

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    rotation = true;
  }
  else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    translation = glm::vec2(0.0f, Tetris::BRICK_SIZE);
  }
  else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    translation = glm::vec2(-Tetris::BRICK_SIZE, 0.0f);
  }
  else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    translation = glm::vec2(Tetris::BRICK_SIZE, 0.0f);
  }
}

void MoveTetrisDown(Tetris::Tetris& tetris) {
  tetris.Translate({ 0, -Tetris::BRICK_SIZE });
}

}

int main(void)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(Tetris::WINDOW_WIDTH, Tetris::WINDOW_HEIGHT, "OpenGL review", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  const std::string vs_fn{ "res/shaders/shader.vs" };
  const std::string fs_fn{ "res/shaders/shader.fs" };
  Shader shader(vs_fn, fs_fn);

  // load and create texture
  Tetris::Tetris tetris("res/textures/floor.jpg", Tetris::Color::RED);
  Tetris::GameBoard game_board("res/textures/pinkbg.jpg", "res/textures/floor.jpg");

  /* Loop until the user closes the window */
  shader.use();

  float clear_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  glfwSetKeyCallback(window, KeyCallBack);

  Tetris::TetrisTimer tetris_timer(std::chrono::milliseconds(1000));

  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    GLCall(glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    game_board.Render({ 0.0f, 0.0f, }, shader);
    if (!game_board.GameOver()) {
      tetris.Render(shader, { Tetris::SCALE, Tetris::SCALE, 0 });

      if (rotation) {
        tetris.Rotate();
      }
      if (!game_board.Collide(tetris, translation / Tetris::BRICK_SIZE)) {
        if (translation.x != 0 || translation.y != 0) {
          tetris.Translate(translation);
          translation = { 0, 0 };
        }
        tetris_timer.CheckAndFire([](Tetris::Tetris& tetris) {
          tetris.Translate({ 0, Tetris::BRICK_SIZE });
          }, tetris, true);
      }
      else {
        translation = { 0, 0 };
      }

      rotation = false;
    }
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}