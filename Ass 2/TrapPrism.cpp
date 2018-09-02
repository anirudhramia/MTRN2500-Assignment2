#include "TrapPrism.h"
#include "Shape.hpp"
#include <math.h>

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

#define PI 3.14159265358979323846

TPZ::Trapezoidal_Prism::Trapezoidal_Prism() :Shape() {
	x_l = 0.0;
	y_l = 0.0;
	z_l = 0.0;
	l_off = 0.0;
	r_off = 0.0;
}

TPZ::Trapezoidal_Prism::Trapezoidal_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double left_offset, double right_offset) :Shape(_x, _y, _z) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	l_off = left_offset;
	r_off = right_offset;
	updateVertices();
}

TPZ::Trapezoidal_Prism::Trapezoidal_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double left_offset, double right_offset, double _rotation) :Shape(_x, _y, _z, _rotation) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	l_off = left_offset;
	r_off = right_offset;
	updateVertices();
}




void TPZ::Trapezoidal_Prism::updateVertices() {
	/*
			^	 ^Z
			| Y /
			|  /
			| /
	X<------*
	           6-----------7
	         /           /  \
		   /           /     \
		 /  5        /        4
	   2-----------3        /
	  /			*	\     / 
	 /				 \  /
	1-----------------0
*/
	vertices[0][0] = - (x_l / 2);
	vertices[0][1] = 0;
	vertices[0][2] = - (z_l / 2);

	vertices[1][0] = (x_l / 2);
	vertices[1][1] = 0;
	vertices[1][2] = - (z_l / 2);

	vertices[2][0] = (x_l / 2) - l_off;
	vertices[2][1] = y_l;
	vertices[2][2] = - (z_l / 2);

	vertices[3][0] = - (x_l / 2) + r_off;
	vertices[3][1] = y_l;
	vertices[3][2] = - (z_l / 2);

	vertices[4][0] = - (x_l / 2);
	vertices[4][1] = 0;
	vertices[4][2] = (z_l / 2);

	vertices[5][0] = (x_l / 2);
	vertices[5][1] = 0;
	vertices[5][2] = (z_l / 2);

	vertices[6][0] = (x_l / 2) - l_off;
	vertices[6][1] = y_l;
	vertices[6][2] = (z_l / 2);

	vertices[7][0] = - (x_l / 2) + r_off;
	vertices[7][1] = y_l;
	vertices[7][2] = (z_l / 2);
}


void TPZ::Trapezoidal_Prism::draw() {
	updateVertices();
	//saves the current orientation and perspective
	glPushMatrix();
	//saves the current attributes (specifically colour)
	glPushAttrib(GL_CURRENT_BIT);

	//sets the colour and rotations as specified for the prism
	this->setColorInGL();
	//glRotatef(this->rotation, 0, 1, 0);
	this->positionInGL();

	glBegin(GL_QUADS);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //Bottom
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]); //Top
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]); //left
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);

	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //right
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //Front
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);

	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]); //Back
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	glEnd();
	//restores the previous orientation and perspective
	glPopMatrix();
	//restores the previous attributes (specifically colour)
	glPopAttrib();
}