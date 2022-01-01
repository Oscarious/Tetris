#include "ElementArrayBuffer.h"
#include "common/GLHelper.h"

ElementArrayBuffer::ElementArrayBuffer() {}

ElementArrayBuffer::ElementArrayBuffer(unsigned int* indices, unsigned int size, unsigned int count)
  : count_(count)
{
  Init(indices, size, count);
}

void ElementArrayBuffer::Init(unsigned int* indices, unsigned int size, unsigned int count) {
  if (initialized_) {
    std::cout << "WARNING: The EBO has already been initialized" << std::endl;
    return;
  }
  initialized_ = true;
  count_ = count;
  GLCall(glGenBuffers(1, &id_));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}
ElementArrayBuffer::~ElementArrayBuffer()
{
  UnBind();
}

void ElementArrayBuffer::Bind() const
{
  if (!initialized_) {
    std::cout << "ERROR: The EBO has NOT been initialized" << std::endl;
    return;
  }
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
}

void ElementArrayBuffer::UnBind() const
{
  if (!initialized_) {
    std::cout << "ERROR: The EBO has NOT been initialized" << std::endl;
    return;
  }
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int ElementArrayBuffer::Count() const
{
  if (!initialized_) {
    std::cout << "ERROR: The EBO has NOT been initialized" << std::endl;
    return 0;
  }
  return count_;
}
