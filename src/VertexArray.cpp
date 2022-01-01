#include "VertexArray.h"
#include "common/GLHelper.h"

VertexArray::VertexArray()
{
  GLCall(glGenVertexArrays(1, &id_));
  GLCall(glBindVertexArray(id_));
}

VertexArray::~VertexArray()
{
  UnBind();
}

void VertexArray::Bind() const
{
  GLCall(glBindVertexArray(id_));
}

void VertexArray::UnBind() const
{
  GLCall(glBindVertexArray(0));
}
