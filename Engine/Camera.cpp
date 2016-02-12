#include "Camera.h"

namespace Engine
{
	Camera::Camera() :
		_theta(0.0f),
		_phi(0.0f),
		_orientation(),
		_position()
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::init(glm::vec3 position, glm::vec3 orientation)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		_position = position;
		_orientation = orientation;
	}

	void Camera::update(InputManager inputManager, glm::mat4 & modelview)
	{
		move(inputManager);
		modelview = glm::lookAt(_position, _target, glm::vec3(0, 0, 1));
	}

	void Camera::rotate(glm::vec2 xy)
	{
		_theta -= xy.x * CAMERA_SENSIBILITY;
		_phi -= xy.y * CAMERA_SENSIBILITY;

		if (_phi > 89.9) {
			_phi = 89.9;
		}
		if (_phi < -89.9) {
			_phi = -89.9;
		}

		float thetaRad = _theta * M_PI / 180;
		float phiRad = _phi * M_PI / 180;

		_orientation.x = cos(phiRad) * cos(thetaRad);
		_orientation.y = cos(phiRad) * sin(thetaRad);
		_orientation.z = sin(phiRad);

		_target = _position + _orientation;
	}

	void Camera::move(InputManager inputManager)
	{
		if (inputManager.mouseMoved()) {
			rotate(inputManager.getMouseMoves());
		}

		if (inputManager.isKeyDown(SDLK_z)) {
			_position += _orientation * CAMERA_SPEED;
		}
		else if (inputManager.isKeyDown(SDLK_s)) {
			_position -= _orientation * CAMERA_SPEED;
		}

		if (inputManager.isKeyDown(SDLK_q)) {
			_position += glm::normalize(glm::cross(glm::vec3(0, 0, 1), _orientation)) * CAMERA_SPEED;
		}
		else if (inputManager.isKeyDown(SDLK_d)) {
			_position -= glm::normalize(glm::cross(glm::vec3(0, 0, 1), _orientation)) * CAMERA_SPEED;
		}

		if (inputManager.isKeyDown(SDLK_SPACE)) {
			_position += glm::vec3(0, 0, 0.5) * CAMERA_SPEED;
		}
		else if (inputManager.isKeyDown(SDLK_LSHIFT)) {
			_position -= glm::vec3(0, 0, 0.5) * CAMERA_SPEED;
		}

		_target = _position + _orientation;
	}
}
