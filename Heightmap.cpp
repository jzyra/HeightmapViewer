/*!
	* \file Heightmap.cpp
	* \brief Load heightmap's datas.
	* \author Jeremy ZYRA
*/
#include "Heightmap.hpp"

Heightmap::Heightmap(string file) {
	SDL_Surface *img = NULL;
	Uint8 r, g ,b;
	img = IMG_Load(file.c_str());
	if(!img) {
		cerr << "[-] SDL error: " << IMG_GetError() << endl;
		exit(0);
	}
	_width = img->w;
	_height = img->h;
	_matrice = (unsigned char **)malloc(_height*sizeof(unsigned char *));
	for (int i=0; i<_height; ++i) {
		_matrice[i] = (unsigned char *)calloc(_width, sizeof(unsigned char));
	}
	SDL_LockSurface(img);
	for (int i=0; i<_height; ++i) {
		for (int j=0; j<_width; ++j) {
			SDL_GetRGB(getPixel(img, j, i), img->format, &r, &g, &b);
			_matrice[i][j] = (unsigned char)((r+g+b)/3);
		}
	}
	SDL_UnlockSurface(img);
}

Heightmap::~Heightmap() {
	for (int i=0; i<_height; ++i) {
		free(_matrice[i]);
	}
	free(_matrice);
}

unsigned char **Heightmap::getMatrice() const {
	return _matrice;
}

int Heightmap::getWidth() const {
	return _width;
}

int Heightmap::getHeight() const {
	return _height;
}

Uint32 Heightmap:: getPixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp) {
		case 1:
			return *p; 
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16; 
		case 4:
			return *(Uint32 *)p;
		default:
			return 0;
	}   
}

