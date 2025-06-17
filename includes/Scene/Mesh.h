#pragma once

#include "../Libs.h"
#include <vector>

class Mesh {
public:
  Mesh() {};
  ~Mesh() {};
  void setVertexBuffer(BufferID in) { vertexBuffer = in; };
  BufferID getVertexBuffer() { return vertexBuffer; }
  BufferID getVertexBuffer() const { return vertexBuffer; }
  void setIndexBuffer(BufferID in) { indexBuffer = in; };
  BufferID getIndexBuffer() { return indexBuffer; }
  BufferID getIndexBuffer() const { return indexBuffer; }
  std::vector<Vertex> vertices;
  std::vector<uint16_t> indices;

private:
  BufferID vertexBuffer;
  BufferID indexBuffer;
};
