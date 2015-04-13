/*!
	* \file Window.hpp
	* \brief Window class.
	* \author Jeremy ZYRA
*/
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS 1

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Heightmap.hpp"
#include "Landscape.hpp"
#include "Camera.hpp"

#include <iostream>
using namespace std;
using namespace glm;

/*!
	* \class Window
	* \brief Manage SDL window.
*/
class Window {

	public: 
	/*!
		* \brief Window Constructor.
		Window class's constructor.
		* \param Path to heightmap file.
	*/
	Window(string heightmap);	
	/*!
		* \brief Window Destructor.
		Delete pointers.
	*/
	~Window();
	/*!
		* \brief Run 3D viewer.
	*/
	void run();

	private:
	bool _end;
	SDL_Event _ev;
	mat4 _projection;
	mat4 _modelview;
	Camera *_camera;
	Heightmap *_map;
	/*!
		* \brief Manage Window's events.
	*/
	void event();

};

#endif
