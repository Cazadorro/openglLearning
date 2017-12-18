//
// Created by shae on 11/20/17.
//

#include "camera.h"


Camera::Camera(float speed, float sensitivity, float zoom, glm::vec3 position, glm::vec3 up, glm::vec3 front, float yaw,
               float pitch) {

    m_movement_speed = speed;
    m_mouse_sensitivity = sensitivity;
    m_zoom = zoom;
    m_position = position;
    m_world_up = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = m_movement_speed * deltaTime;
    switch(direction){
        case FORWARD:
            m_position += m_front * velocity;
            break;
        case BACKWARD:
            m_position -= m_front * velocity;
            break;
        case LEFT:
            m_position -= m_right * velocity;
            break;
        case RIGHT:
            m_position += m_right * velocity;
            break;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= m_mouse_sensitivity;
    yoffset *= m_mouse_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update m_front, m_right and m_up Vectors using the updated Eular angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    if (m_zoom >= 1.0f && m_zoom <= 45.0f){
        m_zoom -= yoffset;
    }
    if (m_zoom <= 1.0f){
        m_zoom = 1.0f;
    }
    if (m_zoom >= 45.0f){
        m_zoom = 45.0f;
    }

}

void Camera::updateCameraVectors() {
    // Calculate the new m_front vector
    glm::vec3 front;
    front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    front.y = sinf(glm::radians(m_pitch));
    front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    // Also re-calculate the m_right and m_up vector
    m_right = glm::normalize(glm::cross(m_front,
                                        m_world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

float Camera::getZoom() {
    return m_zoom;
}

float Camera::getZoomRad() {
    return glm::radians(m_zoom);
}

