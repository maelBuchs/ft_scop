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
    // glm::vec3 getPos();
    // glm::vec3 getFront();
    // glm::vec3 getUp();
    // float     getFOV();
    // void setPos(glm::vec3 pos);
    // void setFront(glm::vec3 front);
    // void setUp(glm::vec3 up);
    // void setFOV(float fov);
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