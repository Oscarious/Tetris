#pragma once
class ElementArrayBuffer {
public:
  /**
   * This Constructor is for variable declaration,
   * you need to initialize the object manually by calling Init
   * same as ElementArrayBuffer
   */
  ElementArrayBuffer();
  ElementArrayBuffer(unsigned int* indices, unsigned int size, unsigned int count);
  ~ElementArrayBuffer();
  void Init(unsigned int* indices, unsigned int size, unsigned int count);
  void Bind() const;
  void UnBind() const;
  unsigned int Count() const;

private:
  unsigned int id_{};
  unsigned int count_{};
  bool initialized_ = false;
};
