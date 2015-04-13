/*!
	* \file Heightmap.hpp
	* \brief Load heightmap's datas.
	* \author Jeremy ZYRA
*/
#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

/*!
	* \class Heightmap
	* \brief Load heightmap's datas.
*/
class Heightmap {

	public:
	/*!
		* \brief Heightmap Constructor.
		Heightmap class's constructor.
		* \param Path to heightmap file.
	*/
	Heightmap(string file);
	/*!
		* \brief Heightmap Destructor.
		Delete pointers.
	*/
	~Heightmap();
	/*!
		* \brief Accessor on height matrice.
		* \return height matrice.
	*/
	unsigned char **getMatrice() const;
	/*!
		* \brief Accessor on width size image in pixels.
		* \return Width size.
	*/
	int getWidth() const;
	/*!
		* \brief Accessor on height size image in pixels.
		* \return Height size.
	*/
	int getHeight() const;

	private:
	int _height;
	int _width;
	unsigned char **_matrice;
	/*!
		* \brief Function for get pixel's color in image.
		* \param Image in SDL_Surface.
		* \param X position.
		* \param Y position.
		* \return Color in Uint32.
	*/
	Uint32 getPixel(SDL_Surface *surface, int x, int y);

};

#endif
