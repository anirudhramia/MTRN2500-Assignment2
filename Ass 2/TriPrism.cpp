#include "TriPrism.h"
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

//initalise the rectangular prism with zero dimensions
TRI::Triangular_Prism::Triangular_Prism() :Shape() {
	x_l = 0.0;
	slant_l = 0.0;
	z_l = 0.0;
	angle = 0.0;
}

//initalise the rectangular prism with given dimensions
TRI::Triangular_Prism::Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle, double _red, double _green, double _blue):Shape(_x,_y,_z){
	x_l = length_x;
	slant_l = length_slant;
	z_l = length_z;
	angle = _angle;
	this->setColor(_red, _green, _blue);
	updateVertices();

}

//intialise the rectangular prism with given dimensions and rotation
TRI::Triangular_Prism::Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle, double _red, double _green, double _blue, double _rotation) :Shape(_x, _y, _z,_rotation) {
	x_l = length_x;
	slant_l = length_slant;
	z_l = length_z;
	angle = _angle;
	this->setColor(_red, _green, _blue);
	updateVertices();
}
\
// setters for shape dimensions
void TRI::Triangular_Prism::setXLength(double length_x) {
	x_l = length_x;
}

void TRI::Triangular_Prism::setSlantLength(double length_slant) {
	slant_l = length_slant;
}

void TRI::Triangular_Prism::setZLength(double length_z) {
	z_l = length_z;
}

void TRI::Triangular_Prism::setAngle(double _angle) {
	angle = _angle;
}

//maps the vertices array to store the locations of each vertex of the prism, as described below
void TRI::Triangular_Prism::updateVertices(){
/*
		This is the coordinates of the vertex on the triangular prism
			^	 ^Z
			| Y /
			|  /
			| /
	X<------*
	

	        5
	       /  \
		  /     \
		 / 2	  3
		/		  /
	   4    *    /
	  /  \      /
	 /@    \   /
	1--------0

	* represents the x,y,z of the centrepoint shape
	@ represents the angle of the face

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

	// converts the given degree angle to a radian angle
	double rad_angle = PI / 180 * angle;

	vertices[4][0] = (x_l / 2) - slant_l * cos(rad_angle);
	vertices[4][1] = slant_l * sin(rad_angle);
	vertices[4][2] = - (z_l / 2);

	vertices[5][0] = (x_l / 2) - slant_l * cos(rad_angle);
	vertices[5][1] = slant_l * sin(rad_angle);
	vertices[5][2] = (z_l / 2);

}

// draw function
void TRI::Triangular_Prism::draw(){

	updateVertices();

	//saves the current orientation and perspective
	glPushMatrix();
	//saves the current attributes (specifically colour)
	glPushAttrib(GL_CURRENT_BIT);

	//sets the colour and rotations as specified for the prism
	this->setColorInGL();
	//glRotatef(this->rotation, 0, 1, 0);
	this->positionInGL();

	// draws each of the two triangle faces
	glBegin(GL_TRIANGLES);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //Front
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]); //Back
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glEnd();

	// draws the remaining 4 quadrilateral faces
	glBegin(GL_QUADS);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //Bottom
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);

	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //right
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]); //left
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
	glEnd();

	//restores the previous orientation and perspective
	glPopMatrix();
	//restores the previous attributes (specifically colour)
	glPopAttrib();

}
