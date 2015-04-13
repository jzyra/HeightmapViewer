/*!
	* \file Camera.cpp
	* \brief Manage camera.
	* \author Jeremy ZYRA
*/
#include "Camera.hpp"

Camera::Camera(mat4 &modelview, vec3 position, vec3 target) {
	_theta = 0;
	_phi = 0;
	_sensivity = 0.2;
	_modelview = &modelview;
	_position = position;
	_target = target;
	*_modelview = lookAt(_position, _target, vec3(0, 1, 0));
	_forward = vec3(0, 0, 1);
	_left = cross(vec3(0, 1, 0), _forward);
	_left = normalize(_left);
}

void Camera::mouseMotion(int x, int y) {
	double tmp = 0;
	_theta -= x*0.5;
	_phi -= y*0.5;	
	if (_phi>89) {
		_phi = 89;
	} else if (_phi < -89) {
		_phi = -89;
	}
	tmp = cos(_phi*M_PI/180);
	_forward[2] = tmp*cos(_theta*M_PI/180);
	_forward[0] = tmp*sin(_theta*M_PI/180);
	_forward[1] = sin(_phi*M_PI/180);
	_target = _position + _forward;
	_left = cross(vec3(0, 1, 0), _forward);
	_left = normalize(_left);
	*_modelview = lookAt(_position, _target, vec3(0, 1, 0));
}

void Camera::forward() {
	_position += _forward * 10.0f;
	_target += _forward * 10.0f;
	*_modelview = lookAt(_position, _target, vec3(0, 1, 0));
}

void Camera::backware() {
	_position -= _forward * 10.0f;
	_target -= _forward * 10.0f;
	*_modelview = lookAt(_position, _target, vec3(0, 1, 0));
}

void Camera::left() {
	_position += _left *10.0f;	
	_target = _position + _forward;
	*_modelview = lookAt(_position, _target, vec3(0, 1, 0));
}

void Camera::right() {
	_position -= _left *10.0f;
	_target = _position + _forward;
	*_modelview = lookAt(_position, _target, vec3(0, 1, 0));
}
