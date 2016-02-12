#pragma once

#include "InputManager.h"
#include <SDL\SDL.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	const float CAMERA_SPEED = 0.8;
	const float CAMERA_SENSIBILITY = 0.5;

	class Camera
	{
	public:
		Camera();
		~Camera();

		void init(glm::vec3 position, glm::vec3 orientation);
		void update(InputManager inputManager, glm::mat4 & modelview);
		void rotate(glm::vec2 xy);
		void move(InputManager inputManager);

	private:
		float _theta;
		float _phi;
		glm::vec3 _orientation;
		glm::vec3 _position;
		glm::vec3 _target;
	};
}

