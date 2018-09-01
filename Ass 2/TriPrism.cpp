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
	
	vertices[0][0] = x - (x_l / 2);
	vertices[0][1] = y;
	vertices[0][2] = z - (z_l / 2);

	vertices[1][0] = x + (x_l / 2);
	vertices[1][1] = y;
	vertices[1][2] = z - (z_l / 2);

	vertices[2][0] = x + (x_l / 2);
	vertices[2][1] = y;
	vertices[2][2] = z + (z_l / 2);

	vertices[3][0] = x - (x_l / 2);
	vertices[3][1] = y;
	vertices[3][2] = z + (z_l / 2);

	double rad_angle = PI / 180 * angle;

	vertices[4][0] = x + (x_l / 2) - slant_l * cos(rad_angle);
	vertices[4][1] = slant_l * sin(rad_angle);
	vertices[4][2] = z - (z_l / 2);

	vertices[5][0] = x + (x_l / 2) - slant_l * cos(rad_angle);
	vertices[5][1] = slant_l * sin(rad_angle);
	vertices[5][2] = z + (z_l / 2);

}


void TRI::Triangular_Prism::draw(){
	//saves the current orientation and perspective
	glPushMatrix();
	//saves the current attributes (specifically colour)
	glPushAttrib(GL_CURRENT_BIT);

	//sets the colour and rotations as specified for the prism
	this->setColorInGL();
	glRotatef(this->rotation, 0, 1, 0);

	glBegin(GL_TRIANGLES);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glEnd();

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
