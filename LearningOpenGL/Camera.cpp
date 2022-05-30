#include "Camera.h"

//////////////////////////////////
/*		Public Functions		*/
//////////////////////////////////

Camera::Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f))
	: position{ position }
{
	yaw				= DEFAULT_YAW;
	pitch			= DEFAULT_PITCH;
	sensitivity		= DEFAULT_SENSITIVITY;
	movementSpeed	= DEFAULT_MOVEMENT_SPEED;
	worldUp			= glm::vec3(0.0f, 1.0f, 0.0f);
	firstTime		= true;
	updateMovementVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::moveAround(Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;

	switch (direction)
	{
	case Movement::FORWARD:
		position.x += front.x * velocity;
		position.y += front.y * velocity;
		position.z += front.z * velocity;
		break;
	case Movement::BACKWARD:
		position.x -= front.x * velocity;
		position.y -= front.y * velocity;
		position.z -= front.z * velocity;
		break;
	case Movement::LEFT:
		position -= right * velocity;
		break;
	case Movement::RIGHT:
		position += right * velocity;
		break;
	}
}

void Camera::lookAround(float xPos, float yPos)
{
	if (firstTime)
	{
		lastX = xPos;
		lastY = yPos;
		firstTime = false;
	}

	float xDifference = xPos - lastX;
	float yDifference = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	yaw += (xDifference * sensitivity);
	pitch += (yDifference * sensitivity);

	pitch = glm::clamp(pitch, -89.0f, 89.0f);
	updateMovementVectors();
}

glm::vec3 Camera::getPosition()
{
	return position + glm::vec3(0.5, 0.5, 0.5);
}

float Camera::getYaw() const
{
	return yaw;
}

float Camera::getPitch() const
{
	return pitch;
}

glm::vec3 Camera::getDirectionVector()
{
	return front;
}

//////////////////////////////////
/*		Private Functions		*/
//////////////////////////////////

void Camera::updateMovementVectors()
{
	front = glm::normalize(
		glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
		)
	);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


