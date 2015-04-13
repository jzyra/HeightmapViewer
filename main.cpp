/*!
	* \file main.cpp
	* \brief Program's entry point.
	* \author Jeremy ZYRA
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Window.hpp"
#include "Heightmap.hpp"
using namespace std;

/*!
	* \brief Function for print usage.
*/
void printUsage(char *name) {
	cout << "NAME" << endl;
	cout << "\tHeightmapViewer" << endl << endl;
	cout << "SYNOPSIS" << endl;
	cout << "\t" << name << " HEIGHTMAP" << endl << endl; 
	cout << "DESCRIPTION" << endl;
	cout << "\tView 3D result of heightmap." << endl << endl;
	cout << "OPTIONS" << endl;
	cout << "\tPath to image file who contain the heightmap." << endl << endl;
	cout << "AUTHOR" << endl;
	cout << "\tJeremy ZYRA" << endl;
}

/*!
	* \brief Program's entry point.
*/
int main(int argc, char **argv) {
	//Check if there is one parameter.
	if (argc < 2) {
		printUsage(argv[0]);
	} else {
		Window *window = new Window(string(argv[1]));
		window->run();
		delete(window);
	}
	return 0;
}
