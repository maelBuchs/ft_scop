#include "../include/Camera.h"
#include "../include/glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Camera::Camera() {
    pos = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    fov = 55.0f;
}

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov) {
    this->pos = pos;
    this->front = front;
    this->up = up;
    this->fov = fov;
}

Camera::~Camera() {}

void  Camera::goFront(float speed) { pos += speed * front; }
void Camera::goBack(float speed) { pos -= speed * front; }

void Camera::goLeft(float speed) {
    pos -= glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::goRight(float speed) {
    pos += glm::normalize(glm::cross(front, up)) * speed;
}