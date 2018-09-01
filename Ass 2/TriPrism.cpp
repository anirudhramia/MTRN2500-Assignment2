#include "TriPrism.h"
#include "Shape.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif



TRI::Triangular_Prism::Triangular_Prism() :Shape() {
	x_l = 0.0;
	slant_l = 0.0;
	z_l = 0.0;
	angle = 0.0;
}

TRI::Triangular_Prism::Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle):Shape(_x,_y,_z){
	x_l = length_x;
	slant_l = length_slant;
	z_l = length_z;
	angle = _angle;
	updateVertices();

}

TRI::Triangular_Prism::Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle, double _rotation) :Shape(_x, _y, _z,_rotation) {
	x_l = length_x;
	slant_l = length_slant;
	z_l = length_z;
	angle = _angle;
	updateVertices();
}


void TRI::Triangular_Prism::updateVertices(){
/*
			^	 ^Z
			| Y /
			|  /
			| /
	X<------*
	

	        4
	       /  \
		  /     \
		 / 5	  3
		/		  /
	   2    *    /
	  /  \      /
	 /@    \   /
	1--------0

	* represents the x,y,z of the centrepoint shape
	@ represents the angle of the face

*/
	

}



