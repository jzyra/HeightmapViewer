/*!
	* \file Camera.hpp
	* \brief Manage camera.
	* \author Jeremy ZYRA
*/
#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS 1

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;
using namespace std;

/*!
	* \class Camera
	* \brief Manage camera view.
*/
class Camera {
	
	private:
	double _theta;
	double _phi;
	double _sensivity;
	mat4 *_modelview;
	vec3 _position;
	vec3 _target;
	vec3 _forward;
	vec3 _left;

	public:
	/*!
		* \brief Camera Constructor.
		Camera class's constructor.
		* \param ModeleView martix.
		* \param Position's vector.
		* \param Position fixed by camera.
	*/
	Camera(mat4 &modelview, vec3 position, vec3 target);
	/*!
		* \brief Function for move camera when mouse is moved.
		* \param X mouse's position.
		* \param Y mouse's position.
	*/
	void mouseMotion(int x, int y);
	/*!
		* \brief Function for move camera when up button is pressed.
	*/
	void forward();
	/*!
		* \brief Function for move camera when down button is pressed.
	*/
	void backware();
	/*!
		* \brief Function for move camera when left button is pressed.
	*/
	void left();
	/*!
		* \brief Function for move camera when right button is pressed.
	*/
	void right();

};

#endif
