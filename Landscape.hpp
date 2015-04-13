/*!
	* \file Landscape.hpp
	* \brief Display heightmap in 3D view.
	* \author Jeremy ZYRA
*/
#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <GL/glew.h>
#include <cstdlib>
#include <cstdio>
#include "Heightmap.hpp"

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

/*!
	* \class Landscape
	* \brief Display heightmap in 3D view.
*/
class Landscape {

	public:
	/*!
		* \brief Landscape Constructor.
		Landscape class's constructor.
		* \param Heightmap datas.
	*/
	Landscape(const Heightmap &heightmap);
	/*!
		* \brief Landscape Destructor.
		Delete pointers.
	*/
	~Landscape();
	/*!
		* \brief Display 3D landscape.
	*/
	void display() const;

	private:
	float *_vertices;
	float *_colors;
	int _size3;
	int _size6;
	int _height;
	int _width;
	unsigned int *_index;
	unsigned int _vboId;
	unsigned int _iboId;
	/*!
		* \brief Load buffers in graphic card.
	*/
	void loadBufferObject();

};

#endif
