#ifndef  __M_CAMERA_H__
#define  __M_CAMERA_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../_morisa.h"
#include "../m_configture.h"
#include "../utils/m_math.h"
#include "../utils/m_pd.h"

MORISA_NAMESPACE_BEGIN

class m_camera
{
public:
	typedef glm::vec3 vec;
	m_camera() {}

	m_camera(vec position, vec worldUp, float pitch, float yaw) :
		position(position), worldUp(worldUp), pitch(pitch), yaw(yaw)
	{
		updateCameraVectors();
	}

	inline const glm::mat4 getViewMat() const noexcept
	{
		return glm::lookAt(position, position + front, up);
	}

	void keyEvent(GLFWwindow* window, float deltaTime, std::vector<m_type>& wall)
	{
		float _speed_ = speed * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
			return;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += front * _speed_;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= front * _speed_;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += right * _speed_;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= right * _speed_;
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			position -= worldUp * _speed_ / 2.0f;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			position += worldUp * _speed_ / 2.0f;
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			use_collider = true;
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			use_collider = false;

		if (use_collider)
			if (check_collision(wall))
				position = last_position;
		last_position = position;

		updateCameraVectors();
	}

	void mouseCallBack(GLFWwindow* window, float posX, float posY, bool usePitchLock = true)
	{
		if (firstMouse)
		{
			lastX = posX;
			lastY = posY;
			firstMouse = false;
		}
		float offsetX = posX - lastX;
		float offsetY = lastY - posY;
		yaw += offsetX * mouseSensitivity;
		pitch += offsetY * mouseSensitivity;
		if (usePitchLock) pitch = clamp(pitch, 89.0f, -89.0f);
		lastX = posX;
		lastY = posY;
		updateCameraVectors();
	}

	void scrollCallBack(GLFWwindow* window, float Xoffset, float Yoffset)
	{
		fov = clamp(fov - Yoffset, 45.0f, 1.0f);
		updateCameraVectors();
	}

	inline const float getFov()const noexcept { return fov; }

	inline const vec getPosition()const noexcept { return position; }

private:
	vec position{ vec(0.0f, 0.0f, 3.0f) };
	vec last_position{ vec(0.0f, 0.0f, 0.0f) };
	vec worldUp{ vec(0.0f, 1.0f, 0.0f) };

	vec front{ vec(0.0f, 0.0f, -1.0f) };
	vec up{ vec(0.0f, 0.0f, 0.0f) };
	vec right{ vec(0.0f, 0.0f, 0.0f) };

	float yaw{ -90.0f };
	float pitch{ 0.0f };

	float speed{ SPEED };
	float mouseSensitivity{ MOUSE_SENSITIVITY };
	float fov{ 45.0f };

	float deltaTime{ 0.0f };
	float lastTime{ 0.0f };

	float lastX{ 0.0f };
	float lastY{ 0.0f };
	bool firstMouse = {true};

	bool use_collider = {false};
 	
	inline void updateCameraVectors()
	{
		front = glm::normalize(glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}

	bool check_collision(std::vector<m_type>& wall)
	{
		position.y = clamp(position.y, 0.4f, 0.0f);

		auto checkIn = [&](m_position _pos_, float _thresh1_, float _extra1_, float _thresh2_, float _extra2_)->bool 
		{
			return position.x > _pos_.x - _thresh1_ + _extra1_ && position.x < _pos_.x + _thresh1_ + _extra1_
				&& position.z > _pos_.y - _thresh2_ + _extra2_ && position.z < _pos_.y + _thresh2_ + _extra2_;
		};
		for (auto it : wall) {
			bool info = checkIn(it.pos, 3.0f, 0, 3.0f, 0);
			if (info) {
				switch (it.dir)
				{
				case m_direction::forward:
					if (checkIn(it.pos, 0.5f, 0, 0.25f, 0.5f))
						return true;
					break;
				case m_direction::backward:
					if (checkIn(it.pos, 0.5f, 0, 0.25f,-0.5f))
						return true;
					break;
				case m_direction::right:
					if (checkIn(it.pos, 0.25f, 0.5f, 0.5f, 0))
						return true;
					break;
				case m_direction::left:
					if (checkIn(it.pos, 0.25f, -0.5f, 0.5f, 0))
						return true;
					break;
				}
			}
		}
		return false;
	}
};

MORISA_NAMESPACE_END

#endif 

