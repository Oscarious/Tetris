#pragma once
class VertexArray
{
public:
  VertexArray();
  ~VertexArray();
  void Bind() const;
  void UnBind() const;

private:
  unsigned int id_;
};

