/*!
	* \file Window.cpp
	* \brief Window implementation.
	* \author Jeremy ZYRA
*/
#include "Window.hpp"

Window::Window(string heightmap) {
	_end = false;
	_map = new Heightmap(heightmap);
	_projection = perspective(70.0, (double) 800 / 600, 0.001, 200.0);
	_modelview = mat4(1.0);
	//Init camera position.
	_camera = new Camera(_modelview, vec3(_map->getWidth()/2, 77, 0), vec3(_map->getWidth()/2, 0, _map->getHeight()/2));
}

Window::~Window() {
	delete(_map);
	delete(_camera);
}

void Window::event() {
	SDL_WaitEvent(&_ev);
	if (_ev.window.event == SDL_WINDOWEVENT_CLOSE) {
		_end = true;
	}
	switch (_ev.type) {
		case SDL_KEYDOWN:
			switch (_ev.key.keysym.sym) {
				case SDLK_ESCAPE:
					_end = true;
					break;
				case SDLK_UP:
					_camera->forward();
					break;
				case SDLK_DOWN:
					_camera->backware();
					break;
				case SDLK_LEFT:
					_camera->left();
					break;
				case SDLK_RIGHT:
					_camera->right();
					break;
			}
			break;
		break;
		case SDL_MOUSEMOTION:
			_camera->mouseMotion(_ev.motion.xrel, _ev.motion.yrel);
			break;
	}	
}

void Window::run() {
	SDL_Window* window(0);
	SDL_GLContext contextOpenGL(0);
	GLenum initGlew;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[-] SDL error: " << SDL_GetError() << endl;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//Init SDL Window.
	window = SDL_CreateWindow("Viewer 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Init OpenGL context.
	contextOpenGL = SDL_GL_CreateContext(window);
	if (contextOpenGL == 0) {
		cerr << "[-] SDL error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	initGlew = (glewInit());
	if (initGlew != GLEW_OK) {
    cerr << "[-] GLEW error: " << glewGetErrorString(initGlew) << endl;
		SDL_GL_DeleteContext(contextOpenGL);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	//Load Shaders
	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");
	shader.load();
	Landscape landscape(*_map);
	//Main loop
	while (!_end) {
		event();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader.getProgramId());
		//Send modelview and projection matrix to Shader.
		glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "modelview"), 1, GL_FALSE, value_ptr(_modelview));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "projection"), 1, GL_FALSE, value_ptr(_projection));
		//Display map.
		landscape.display();
		glUseProgram(0);
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(contextOpenGL);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
