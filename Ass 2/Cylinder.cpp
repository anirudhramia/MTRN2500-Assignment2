#include "Cylinder.h"
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


// initalise cylinder with zero dimensions
CYL::Cylinder::Cylinder() :Shape() {
	outer_radius = 0.0;
	depth = 0.0;
}

// initialise cylinder with given dimensions and default rotation
CYL::Cylinder::Cylinder(double _x, double _y, double _z, double _outer_radius, double _depth, double _red, double _green, double _blue) :Shape(_x, _y, _z) {
	outer_radius = _outer_radius;
	depth = _depth;
	this->setColor(_red, _green, _blue);
}

// initialise cylidner with given dimensions and rotation
CYL::Cylinder::Cylinder(double _x, double _y, double _z, double _outer_radius, double _depth, double _red, double _green, double _blue, double _rotation) :Shape(_x, _y, _z, _rotation) {
	outer_radius = _outer_radius;
	depth = _depth;
	this->setColor(_red, _green, _blue);
}

// setters for radius and depth
void CYL::Cylinder::setOuterRadius(double _outer_radius) {
	this->outer_radius = _outer_radius;
}

void CYL::Cylinder::setDepth(double _depth) {
	this->depth = _depth;
}

// draws the shape
void CYL::Cylinder::draw() {

	GLUquadricObj *disk1; // One face of cylinder
	GLUquadricObj *disk2; // Second face of cylinder
	GLUquadricObj *cylinder; // Body of cylinder

	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();
	cylinder = gluNewQuadric();

	glPushAttrib(GL_CURRENT_BIT);

	// draw cylinder

	this->setColorInGL();
	glPushMatrix();
	 
	//glRotatef(this->rotation, 0, 1, 0);
	this->positionInGL();
	// draw outer cylinder
	glPushMatrix();
	glTranslatef(0, outer_radius, - (depth / 2));
	gluCylinder(cylinder, outer_radius, outer_radius, depth, 25, 1);
	glPopMatrix();
	
	// draw disk1
	glPushMatrix();
	glTranslatef(0, outer_radius, - (depth / 2));
	gluDisk(disk1, 0, outer_radius, 25, 1);
	glPopMatrix();

	// draw disk2
	glPushMatrix();
	glTranslatef(0, outer_radius, (depth / 2));
	gluDisk(disk2, 0, outer_radius, 25, 1);
	glPopMatrix();

	glPopMatrix();

	glPopAttrib();
}
