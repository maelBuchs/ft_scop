#include "../includes/Includes.h"

Scene::~Scene() {};

void Scene::createCube() {
  Mesh mesh;

  mesh.vertices = {
      // Front face
      {{-0.5f, -0.5f, 0.5f}, {1, 0, 0}},
      {{0.5f, -0.5f, 0.5f}, {0, 1, 0}},
      {{0.5f, 0.5f, 0.5f}, {0, 0, 1}},
      {{-0.5f, 0.5f, 0.5f}, {1, 1, 0}},
      // Back face
      {{-0.5f, -0.5f, -0.5f}, {1, 0, 1}},
      {{0.5f, -0.5f, -0.5f}, {0, 1, 1}},
      {{0.5f, 0.5f, -0.5f}, {1, 1, 1}},
      {{-0.5f, 0.5f, -0.5f}, {0, 0, 0}},
  };

  mesh.indices = {
      // Front
      0,
      1,
      2,
      2,
      3,
      0,
      // Right
      1,
      5,
      6,
      6,
      2,
      1,
      // Back
      5,
      4,
      7,
      7,
      6,
      5,
      // Left
      4,
      0,
      3,
      3,
      7,
      4,
      // Top
      3,
      2,
      6,
      6,
      7,
      3,
      // Bottom
      4,
      5,
      1,
      1,
      0,
      4,
  };
  mesh.setVertexBuffer(bufferManager->createVertexBuffer(mesh.vertices));
  mesh.setIndexBuffer(bufferManager->createIndexBuffer(mesh.indices));
  // mesh.indexCount = static_cast<uint32_t>(mesh.indices.size());

  // Ajoute le mesh à la scène
  int meshIndex = static_cast<int>(meshes.size());
  meshes.push_back(std::move(mesh));

  // Crée un objet 3D
  Obj3d obj;
  obj.setMeshIndex(meshIndex);
  obj.setModelMatrix(glm::mat4(1.0f)); // Identité

  // Ajoute l'objet à la scène
  objs3d.push_back(std::move(obj));
}