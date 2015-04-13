/*!
	* \file Shader.cpp
	* \brief Load shader.
	* \author Jeremy ZYRA
*/
#include "Shader.hpp"

Shader::Shader(string vertexSource, string fragmentSource) {
	_vertexId = 0;
	_fragmentId = 0;
	_programId = 0;
	_vertexSource = vertexSource;
	_fragmentSource = fragmentSource;
}

Shader::~Shader() {
    glDeleteShader(_vertexId);
    glDeleteShader(_fragmentId);
    glDeleteProgram(_programId);
}

bool Shader::load() {
	if(glIsShader(_vertexId) == GL_TRUE)
		glDeleteShader(_vertexId);
	if(glIsShader(_fragmentId) == GL_TRUE)
		glDeleteShader(_fragmentId);
	if(glIsProgram(_programId) == GL_TRUE)
		glDeleteProgram(_programId);
	if(!compilerShader(_vertexId, GL_VERTEX_SHADER, _vertexSource))
		return false;
	if(!compilerShader(_fragmentId, GL_FRAGMENT_SHADER, _fragmentSource))
		return false;
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexId);
	glAttachShader(_programId, _fragmentId);
	glBindAttribLocation(_programId, 0, "in_Vertex");
	glBindAttribLocation(_programId, 1, "in_Color");
	glBindAttribLocation(_programId, 2, "in_TexCoord0");
	glLinkProgram(_programId);
	GLint errorLink(0);
	glGetProgramiv(_programId, GL_LINK_STATUS, &errorLink);
	if(errorLink != GL_TRUE) {
		GLint sizeError(0);
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &sizeError);
		char *error = new char[sizeError + 1];
		glGetShaderInfoLog(_programId, sizeError, &sizeError, error);
		error[sizeError] = '\0';
		cerr << error << endl;
		delete[] error;
		glDeleteProgram(_programId);
		return false;
	} else
		return true;
}

bool Shader::compilerShader(GLuint &shader, GLenum type, string const &fileSource) {
	shader = glCreateShader(type);
	if(shader == 0) {
		cerr << "Error, shader's type (" << type << ") does not exist." << endl;
		return false;
	}
	ifstream file(fileSource.c_str());
	if(!file) {
		cerr << "Error, this file " << fileSource << " is not found." << endl;
		glDeleteShader(shader);
		return false;
	}
	string line;
	string sourceCode;
	while(getline(file, line))
		sourceCode += line + '\n';
	file.close();
	const GLchar* chaineCodeSource = sourceCode.c_str();
 	glShaderSource(shader, 1, &chaineCodeSource, 0);
	glCompileShader(shader);
	GLint errorCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &errorCompilation);
	if(errorCompilation != GL_TRUE) {
		GLint sizeError(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &sizeError);
		char *error = new char[sizeError + 1];
		glGetShaderInfoLog(shader, sizeError, &sizeError, error);
		error[sizeError] = '\0';
		cerr << error << endl;
		delete[] error;
		glDeleteShader(shader);
		return false;
	} else
		return true;
}

GLuint Shader::getProgramId() const {
	return _programId;
}
