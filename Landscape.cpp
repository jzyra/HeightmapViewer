/*!
	* \file Landscape.cpp
	* \brief Display heightmap in 3D view.
	* \author Jeremy ZYRA
*/
#include "Landscape.hpp"

Landscape::Landscape(const Heightmap &heightmap) {
	int index, count;
	unsigned char **matrice = heightmap.getMatrice();
	count = _iboId =_vboId = 0;
	_height = heightmap.getHeight();
	_width = heightmap.getWidth();
	_size3 = ((_height*_width)*sizeof(float))*3;
	_size6 = (((_height-1)*(_width-1))*sizeof(unsigned int))*6;
	_vertices = (float *)malloc(_size3);	
	_colors = (float *)malloc(_size3);	
	_index = (unsigned int *)malloc(_size6);	
	for (int y=0; y<_height; ++y) {
		for (int x=0; x<_width; ++x) {
			index = (y*(_width*3))+(x*3);
			//Vertices postions.
			_vertices[index] = (float)x;
			_vertices[index+1] = (float)matrice[y][x];
			_vertices[index+2] = (float)y;
			//Vertices colors
			_colors[index] = 0.0;
			_colors[index+1] = 1.0;
			_colors[index+2] = 0.0;
			//Index matrix.
			if (x<_width-1 && y<_height-1) {
				_index[count] = (y*_width)+x;
				_index[count+1] = ((y+1)*_width)+x;
				_index[count+2] = (y*_width)+(x+1);
				_index[count+3] = ((y+1)*_width)+(x+1);
				_index[count+4] = ((y+1)*_width)+x;
				_index[count+5] = (y*_width)+(x+1);
				count += 6;
			}
		}
	}
	loadBufferObject();
}

Landscape::~Landscape() {
	glDeleteBuffers(1, &_vboId);
	glDeleteBuffers(1, &_iboId);
	free(_vertices);
	free(_colors);
	free(_index);
}

void Landscape::loadBufferObject() {
	//Load VBO
	if(glIsBuffer(_vboId) == GL_TRUE)
		glDeleteBuffers(1, &_vboId);
	glGenBuffers(1, &_vboId);	
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, (_size3*2), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _size3, _vertices);
	glBufferSubData(GL_ARRAY_BUFFER, _size3, _size3, _colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Load IBO
	if(glIsBuffer(_iboId) == GL_TRUE)
		glDeleteBuffers(1, &_iboId);
	glGenBuffers(1, &_iboId);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size6, _index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Landscape::display() const {
	//Vertices
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	//Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(_size3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
	glDrawElements(GL_TRIANGLES, ((_height-1)*(_width-1))*6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0); 
}
