#include "Camera.h"

namespace TE
{
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), position(position), worldUp(up), yaw(yaw), pitch(pitch)
{   
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch)
{
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(EDirection direction, float deltaTime)
{
    float velocity = settings.speed * deltaTime;
    if (direction == EDirection::Forward)
        position += front * velocity;
    if (direction == EDirection::Backward)
        position -= front * velocity;
    if (direction == EDirection::Left)
        position -= right * velocity;
    if (direction == EDirection::Right)
        position += right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= settings.sensitivity;
    yoffset *= settings.sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update front, right and up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    settings.zoom -= (float)yoffset;
    if (settings.zoom < 1.0f)
        settings.zoom = 1.0f;
    if (settings.zoom > 45.0f)
        settings.zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    right = glm::normalize(glm::cross(this->front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, this->front));
}
}

