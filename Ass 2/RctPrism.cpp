#include "RctPrism.h"
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



RCT::Rectangular_Prism::Rectangular_Prism():Shape() {
	x_l = 0.0;
	y_l = 0.0;
	z_l = 0.0;
}


RCT::Rectangular_Prism::Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z) :Shape(_x, _y, _z) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	this->updateVerticies();
}


RCT::Rectangular_Prism::Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z,double _rotation) :Shape(_x, _y, _z,_rotation) {
	x_l = length_x;
	y_l = length_y;
	z_l = length_z;
	this->updateVerticies();
}

void RCT::Rectangular_Prism::updateVerticies() {
	
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
		|		| /
		1------	0
*/
/*	vertices[0] = { x - (x_l / 2), y - (y_l / 2), z };
	vertices[1] = { x + (x_l / 2), y - (y_l / 2), z };
	vertices[2] = { x + (x_l / 2), y + (y_l / 2), z };
	vertices[3] = { x - (x_l / 2), y + (y_l / 2), z };
	vertices[4] = { x - (x_l / 2), y - (y_l / 2), z +z_l };
	vertices[5] = { x + (x_l / 2), y - (y_l / 2), z + z_l };
	vertices[6] = { x + (x_l / 2), y + (y_l / 2), z + z_l };
	vertices[7] = { x - (x_l / 2), y + (y_l / 2), z + z_l };*/	


	vertices[0][0] = x - (x_l / 2);
	vertices[0][1] = y;
	vertices[0][2] = z - (z_l/2);
	
	vertices[1][0] = x + (x_l / 2);
	vertices[1][1] = y;
	vertices[1][2] = z - (z_l / 2);
	
	vertices[2][0] = x + (x_l / 2);
	vertices[2][1] = y;
	vertices[2][2] = z + (z_l / 2);
	
	vertices[3][0] = x - (x_l / 2);
	vertices[3][1] = y;
	vertices[3][2] = z + (z_l / 2);
	
	vertices[4][0] = x - (x_l / 2);
	vertices[4][1] = y + y_l;
	vertices[4][2] = z - (z_l / 2);
	
	vertices[5][0] = x + (x_l / 2);
	vertices[5][1] = y + y_l;
	vertices[5][2] = z - (z_l / 2);
	
	vertices[6][0] = x + (x_l / 2);
	vertices[6][1] = y + y_l;
	vertices[6][2] = z + (z_l / 2);
	
	vertices[7][0] = x - (x_l / 2);
	vertices[7][1] = y + y_l;
	vertices[7][2] = z + (z_l / 2);
}

void RCT::Rectangular_Prism::draw() {
	glPushMatrix();
	glRotatef(this->rotation, 0, 1, 0);
	//glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]); //0
	//glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]); //1
	//glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]); //2
	//glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]); //3
	//glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]); //4
	//glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]); //5
	//glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]); //6
	//glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]); //7
	

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
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
	//glEnd();

	//glBegin(GL_QUADS);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glEnd();
	glPopMatrix();
}