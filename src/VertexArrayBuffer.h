#pragma once
class VertexArrayBuffer
{
public:
  /**
   * This Constructor is for variable declaration, 
   * you need to initialize the object manually by calling Init
   * same as ElementArrayBuffer
   */
  VertexArrayBuffer();
  VertexArrayBuffer(float* vertices, unsigned int size, unsigned int count);
  ~VertexArrayBuffer();
  void Init(float* vertices, unsigned int size, unsigned int count);
  void Bind() const;
  void UnBind() const;
  void AssignAttribPointer(unsigned int layout, int size, unsigned int stride, const void* ptr) const;
  unsigned int Count() const;

private:
  unsigned int id_{};
  unsigned int count_{};
  bool initialized_ = false;
};

