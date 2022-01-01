#pragma once
#include <string>
#include <glm/glm.hpp>

class Texture2D
{
public:
  Texture2D();
  Texture2D(const std::string& img_fn);
  Texture2D(Texture2D&) = delete;
  Texture2D(Texture2D&& other) noexcept;
  ~Texture2D();

  void Bind() const;
  void UnBind() const;

private:
  unsigned int id_{};

  void LoadExternalImage(const std::string& image_fn);

};

