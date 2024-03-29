#include "RctPrism.h"
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


//initalise the rectangular prism with zero dimensions
RCT::Rectangular_Prism::Rectangular_Prism():Shape() { 
	x_l = 0.0;
	y_l = 0.0;
	z_l = 0.0;
}

//initalise the rectangular prism with given dimensions
RCT::Rectangular_Prism::Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double _red, double _green, double _blue) :Shape(_x, _y, _z) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	this->setColor(_red, _green, _blue);
	this->updateVertices(); //update the location of the vertices
}

//intialise the rectangular prism with given dimensions and rotation
RCT::Rectangular_Prism::Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double _red, double _green, double _blue, double _rotation) :Shape(_x, _y, _z,_rotation) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	this->setColor(_red, _green, _blue);
	this->updateVertices(); //update the location of the vertices
}

//Setters for the x,y,z lengths
void RCT::Rectangular_Prism::setXLength(double length_x)
{
	x_l = length_x;
}

void RCT::Rectangular_Prism::setYLength(double length_y)
{
	y_l = length_y;
}

void RCT::Rectangular_Prism::setZLength(double length_z)
{
	z_l = length_z;
}


//maps the vertices array to store the locations of each vertex of the prism, as described below
void RCT::Rectangular_Prism::updateVertices() {
	
/*
			This is the coordinates of the vertices on the rectangular prism
		    ^	 ^Z
			| Y /
			|  /
			| /
	X<------*
		  
			6------	7
		  /		  / |
		5------	4	|
		|		|	|		
		|		|	|
		|	2	|	3
		|	 *	| /
		1------	0
	
	* represents the x,y,z of the centrepoint shape
*/

	vertices[0][0] = - (x_l / 2);
	vertices[0][1] = 0;
	vertices[0][2] = - (z_l / 2);

	vertices[1][0] = (x_l / 2);
	vertices[1][1] = 0;
	vertices[1][2] = - (z_l / 2);

	vertices[2][0] = (x_l / 2);
	vertices[2][1] = 0;
	vertices[2][2] = (z_l / 2);

	vertices[3][0] = - (x_l / 2);
	vertices[3][1] = 0;
	vertices[3][2] = (z_l / 2);

	vertices[4][0] = - (x_l / 2);
	vertices[4][1] = y_l;
	vertices[4][2] = - (z_l / 2);

	vertices[5][0] = (x_l / 2);
	vertices[5][1] = y_l;
	vertices[5][2] = - (z_l / 2);

	vertices[6][0] = (x_l / 2);
	vertices[6][1] = y_l;
	vertices[6][2] = (z_l / 2);

	vertices[7][0] = - (x_l / 2);
	vertices[7][1] = y_l;
	vertices[7][2] = (z_l / 2);
}

//draws the shape
void RCT::Rectangular_Prism::draw() {

	updateVertices();

	//saves the current orientation and perspective
	glPushMatrix();
	//saves the current attributes (specifically colour)
	glPushAttrib(GL_CURRENT_BIT);

	//sets the colour and rotations as specified for the prism
	this->setColorInGL();
	//glRotatef(this->rotation, 0, 1, 0);
	this->positionInGL();
	
	//draws each of the 6 quad faces of the prism
	glBegin(GL_QUADS);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //Bottom
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glEnd();

	
	glBegin(GL_QUADS);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]); //Top
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]); 
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]); 
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	//glEnd();

	
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //Front
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
	//glEnd();
	
	//glBegin(GL_QUADS);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]); //Back
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	//glEnd();

	//glBegin(GL_QUADS);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //right
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
	//glEnd();

	//glBegin(GL_QUADS);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]); //left
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glEnd();
	//restores the previous orientation and perspective
	glPopMatrix();
	//restores the previous attributes (specifically colour)
	glPopAttrib();
}