#include "Texture2D.h"
#include "common/GLHelper.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// 1x1 WHITE color texture
Texture2D::Texture2D() {
  GLCall(glGenTextures(1, &id_));
  GLCall(glBindTexture(GL_TEXTURE_2D, id_));
  // wrapping parameter
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // filtering parameter
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  unsigned int data = 0xffffffff;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA8, GL_UNSIGNED_BYTE, &data);
}

Texture2D::Texture2D(const std::string& img_fn)
{
  GLCall(glGenTextures(1, &id_));
  GLCall(glBindTexture(GL_TEXTURE_2D, id_));
  // wrapping parameter
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // filtering parameter
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  LoadExternalImage(img_fn);
}

Texture2D::Texture2D(Texture2D&& other) noexcept {
  id_ = other.id_;
}

Texture2D::~Texture2D()
{
  UnBind();
}

void Texture2D::Bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture2D::UnBind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::LoadExternalImage(const std::string& image_fn)
{
  // read image data
  int width{}, height{}, nr_channels{};
  //stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(image_fn.c_str(), &width, &height, &nr_channels, 0);
  if (data == NULL) {
    throw std::runtime_error("Failed to load image: " + image_fn);
  }
  if (nr_channels == 4) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }
  else if (nr_channels == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  }
  else {
    std::cout << "channels = " << nr_channels << std::endl;
    throw std::runtime_error("Image channels not supported yet: channels = ");
  }
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  data = nullptr;
}
