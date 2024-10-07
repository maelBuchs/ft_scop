#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
  public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 front,
      glm::vec3 up, float fov);
    ~Camera();
    void goFront(float speed);    
    void goBack(float speed);
    void goLeft(float speed);
    void goRight(float speed);    
    glm::vec3 pos; 
    glm::vec3 front ;
    glm::vec3 up;
    float fov;
  private:


};

#endif