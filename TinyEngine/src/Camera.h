#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Core.h"



namespace TE
{
    enum class EDirection
    {
        Forward,
        Backward,
        Left,
        Right
    };
    
    class TE_API Camera
    {
        struct CameraSettings
        {
            float speed       =  2.5f;
            float sensitivity =  0.1f;
            float zoom        =  45.0f;
    
        };
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch =  0.0f);
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    
        glm::mat4 GetView();

        void ProcessKeyboard(EDirection direction, float deltaTime);

        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

        void ProcessMouseScroll(float yoffset);

        glm::vec3 GetPosition() const { return position; }
        glm::vec3 GetFront() const { return front; }
        glm::vec3 GetUp() const { return up; }
        glm::vec3 GetRight() const { return right; }
        float GetZoom() const { return settings.zoom; }

    private:
        void UpdateCameraVectors();
    
        // camera Attributes
        glm::vec3 position;
    
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        // euler Angles
        float yaw;
        float pitch;

        CameraSettings settings;
    };
}
