/*!
	* \file Shader.hpp
	* \brief Load shader.
	* \author Jeremy ZYRA
*/
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*!
	* \class Shader
	* \brief Load shader program.
*/
class Shader {

	public:
	/*!
		* \brief Shader Constructor.
		Heightmap class's constructor.
		* \param Path to vertex shader file.
		* \param Path to fragment shader file.
	*/
	Shader(string vertexSource, string fragmentSource);
	/*!
		* \brief Shader Destructor.
		Delete pointers.
	*/
	~Shader();
	/*!
		* \brief Load shaders.
	*/
	bool load();
	/*!
		* \brief Accessor to id program shader.
		\return shader's id
	*/
	GLuint getProgramId() const;

	private:
	GLuint _vertexId;
	GLuint _fragmentId;
	GLuint _programId;
	string _vertexSource;
	string _fragmentSource;
	/*!
		* \brief Function for compile shader.
		\param Shader's id.
		\param Shader's type (Fragment or Vertex Shader).
		\param Path to source file.
		\return true if shader is compiled.
	*/
	bool compilerShader(GLuint &shader, GLenum type, string const &fileSource);

};

#endif
