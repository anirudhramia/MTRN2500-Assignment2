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


//initalise the rectangular prism with dimensions 0x0x0
RCT::Rectangular_Prism::Rectangular_Prism():Shape() { 
	x_l = 0.0;
	y_l = 0.0;
	z_l = 0.0;
	
}

//initalise the rectangular prism with given dimensions
RCT::Rectangular_Prism::Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z) :Shape(_x, _y, _z) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	this->updateVerticies(); //update the location of the verticies
}

//intialise the rectangular prism with given dimensions and rotation
RCT::Rectangular_Prism::Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z,double _rotation) :Shape(_x, _y, _z,_rotation) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	this->updateVerticies(); //update the location of the verticies
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


//maps the verticies array to store the locations of each vertex of the prism, as described below
void RCT::Rectangular_Prism::updateVerticies() {
	
/*
			This is the coordinates of the verticies on the rectangular prism
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


/*	These are the coordinates of each vertex
	verticies[0] = { x - (x_l / 2), y - (y_l / 2), z };
	verticies[1] = { x + (x_l / 2), y - (y_l / 2), z };
	verticies[2] = { x + (x_l / 2), y + (y_l / 2), z };
	verticies[3] = { x - (x_l / 2), y + (y_l / 2), z };
	verticies[4] = { x - (x_l / 2), y - (y_l / 2), z +z_l };
	verticies[5] = { x + (x_l / 2), y - (y_l / 2), z + z_l };
	verticies[6] = { x + (x_l / 2), y + (y_l / 2), z + z_l };
	verticies[7] = { x - (x_l / 2), y + (y_l / 2), z + z_l };*/	


	verticies[0][0] = x - (x_l / 2);
	verticies[0][1] = y;
	verticies[0][2] = z - (z_l/2);
	
	verticies[1][0] = x + (x_l / 2);
	verticies[1][1] = y;
	verticies[1][2] = z - (z_l / 2);
	
	verticies[2][0] = x + (x_l / 2);
	verticies[2][1] = y;
	verticies[2][2] = z + (z_l / 2);
	
	verticies[3][0] = x - (x_l / 2);
	verticies[3][1] = y;
	verticies[3][2] = z + (z_l / 2);
	
	verticies[4][0] = x - (x_l / 2);
	verticies[4][1] = y + y_l;
	verticies[4][2] = z - (z_l / 2);
	
	verticies[5][0] = x + (x_l / 2);
	verticies[5][1] = y + y_l;
	verticies[5][2] = z - (z_l / 2);
	
	verticies[6][0] = x + (x_l / 2);
	verticies[6][1] = y + y_l;
	verticies[6][2] = z + (z_l / 2);
	
	verticies[7][0] = x - (x_l / 2);
	verticies[7][1] = y + y_l;
	verticies[7][2] = z + (z_l / 2);
}

//draws the shape
void RCT::Rectangular_Prism::draw() {

	//saves the current orientation and perspective
	glPushMatrix();
	//saves the current attributes (specifically colour)
	glPushAttrib(GL_CURRENT_BIT);

	//sets the colour and rotations as specified for the prism
	this->setColorInGL();
	glRotatef(this->rotation, 0, 1, 0);

	
	//draws each of the 6 quad faces of the prism
	glBegin(GL_QUADS);
	glVertex3f(verticies[0][0], verticies[0][1], verticies[0][2]); //Bottom
	glVertex3f(verticies[1][0], verticies[1][1], verticies[1][2]);
	glVertex3f(verticies[2][0], verticies[2][1], verticies[2][2]);
	glVertex3f(verticies[3][0], verticies[3][1], verticies[3][2]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(verticies[4][0], verticies[4][1], verticies[4][2]); //Top
	glVertex3f(verticies[5][0], verticies[5][1], verticies[5][2]); 
	glVertex3f(verticies[6][0], verticies[6][1], verticies[6][2]); 
	glVertex3f(verticies[7][0], verticies[7][1], verticies[7][2]);
	//glEnd();

	glVertex3f(verticies[0][0], verticies[0][1], verticies[0][2]); //Front
	glVertex3f(verticies[1][0], verticies[1][1], verticies[1][2]);
	glVertex3f(verticies[5][0], verticies[5][1], verticies[5][2]);
	glVertex3f(verticies[4][0], verticies[4][1], verticies[4][2]);
	//glEnd();

	//glBegin(GL_QUADS);
	glVertex3f(verticies[3][0], verticies[3][1], verticies[3][2]); //Back
	glVertex3f(verticies[2][0], verticies[2][1], verticies[2][2]);
	glVertex3f(verticies[6][0], verticies[6][1], verticies[6][2]);
	glVertex3f(verticies[7][0], verticies[7][1], verticies[7][2]);
	//glEnd();

	//glBegin(GL_QUADS);
	glVertex3f(verticies[0][0], verticies[0][1], verticies[0][2]); //right
	glVertex3f(verticies[3][0], verticies[3][1], verticies[3][2]);
	glVertex3f(verticies[7][0], verticies[7][1], verticies[7][2]);
	glVertex3f(verticies[4][0], verticies[4][1], verticies[4][2]);
	//glEnd();

	//glBegin(GL_QUADS);
	glVertex3f(verticies[1][0], verticies[1][1], verticies[1][2]); //left
	glVertex3f(verticies[2][0], verticies[2][1], verticies[2][2]);
	glVertex3f(verticies[6][0], verticies[6][1], verticies[6][2]);
	glVertex3f(verticies[5][0], verticies[5][1], verticies[5][2]);
	glEnd();
	//restores the previous orientation and perspective
	glPopMatrix();
	//restores the previous attributes (specifically colour)
	glPopAttrib();
}