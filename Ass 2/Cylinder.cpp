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



CYL::Cylinder::Cylinder() :Shape() {
	inner_radius = 0.0;
	outer_radius = 0.0;
	depth = 0.0;
}


CYL::Cylinder::Cylinder(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth) :Shape(_x, _y, _z) {
	inner_radius = _inner_radius;
	outer_radius = _outer_radius;
	depth = _depth;
}


CYL::Cylinder::Cylinder(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _rotation) :Shape(_x, _y, _z, _rotation) {
	inner_radius = _inner_radius;
	outer_radius = _outer_radius;
	depth = _depth;
}

void CYL::Cylinder::setInnerRadius(double _inner_radius) {
	this->inner_radius = _inner_radius;
}

void CYL::Cylinder::setOuterRadius(double _outer_radius) {
	this->outer_radius = _outer_radius;
}

void CYL::Cylinder::setDepth(double _depth) {
	this->depth = _depth;
}

void CYL::Cylinder::draw() {

	GLUquadricObj *disk1; // One face of cylinder
	GLUquadricObj *disk2; // Second face of cylinder
	GLUquadricObj *cylinder; // Body of cylinder
	GLUquadricObj *inner_cylinder; // inner body of cylinder, for hollow cylinders

	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();
	cylinder = gluNewQuadric();
	inner_cylinder = gluNewQuadric();

	glPushAttrib(GL_CURRENT_BIT);
	// draw cylinder

	this->setColorInGL();
	glPushMatrix();

	glRotatef(this->rotation, 0, 1, 0);
	
	// draw outer cylinder
	glPushMatrix();
	glTranslatef(x, y + outer_radius, z - (depth / 2));
	gluCylinder(cylinder, outer_radius, outer_radius, depth, 25, 1);
	glPopMatrix();

	// draw inner cylinder
	glPushMatrix();
	glTranslatef(x, y + outer_radius, z - (depth / 2));
	gluCylinder(cylinder, inner_radius, inner_radius, depth, 25, 1);
	glPopMatrix();
	
	// draw disk1
	glPushMatrix();
	glTranslatef(x, y + outer_radius, z - (depth / 2));
	gluDisk(disk1, inner_radius, outer_radius, 25, 1);
	glPopMatrix();

	// draw disk2
	glPushMatrix();
	glTranslatef(x, y + outer_radius, z + (depth / 2));
	gluDisk(disk2, inner_radius, outer_radius, 25, 1);
	glPopMatrix();

	glPopMatrix();

	glPopAttrib();
}
