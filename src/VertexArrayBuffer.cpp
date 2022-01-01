#include "VertexArrayBuffer.h"
#include "common/GLHelper.h"

VertexArrayBuffer::VertexArrayBuffer() {}

VertexArrayBuffer::VertexArrayBuffer(float* vertices, unsigned int size, unsigned int count)
  : count_(count)
{
  Init(vertices, size, count);
}

void VertexArrayBuffer::Init(float* vertices, unsigned int size, unsigned int count) {
  if (initialized_) {
    std::cout << "WARNING: The VBO has already been initialized" << std::endl;
    return;
  }
  count_ = count;
  initialized_ = true;
  GLCall(glGenBuffers(1, &id_));
  Bind();
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexArrayBuffer::~VertexArrayBuffer()
{
  UnBind();
}

void VertexArrayBuffer::Bind() const
{
  if (!initialized_) {
    std::cout << "ERROR: The VBO has NOT been initialized" << std::endl;
    return;
  }
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));

}

void VertexArrayBuffer::UnBind() const
{
  if (!initialized_) {
    std::cout << "ERROR: The VBO has NOT been initialized" << std::endl;
    return;
  }
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexArrayBuffer::AssignAttribPointer(unsigned int layout, int count, unsigned int stride, const void* ptr) const {
  if (!initialized_) {
    std::cout << "ERROR: The VBO has NOT been initialized" << std::endl;
    return;
  }
  GLCall(glVertexAttribPointer(layout, count, GL_FLOAT, GL_FALSE, stride, ptr));
  GLCall(glEnableVertexAttribArray(layout));
}

unsigned int VertexArrayBuffer::Count() const
{
  if (!initialized_) {
    std::cout << "ERROR: The VBO has NOT been initialized" << std::endl;
    return 0;
  }
  return count_;
}
