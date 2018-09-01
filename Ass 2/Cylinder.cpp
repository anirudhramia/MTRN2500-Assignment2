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
	radius = 0.0;
	depth = 0.0;
}


CYL::Cylinder::Cylinder(double _x, double _y, double _z, double _radius, double _depth) :Shape(_x, _y, _z) {
	radius = _radius;
	depth = _depth;
}


CYL::Cylinder::Cylinder(double _x, double _y, double _z, double _radius, double _depth, double _rotation) :Shape(_x, _y, _z, _rotation) {
	radius = _radius;
	depth = _depth;
}


void CYL::Cylinder::draw() {

	GLUquadricObj *disk1; // One face of cylinder
	GLUquadricObj *disk2; // Second face of cylinder
	GLUquadricObj *cylinder; // Body of cylinder

	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();
	cylinder = gluNewQuadric();

	// draw cylinder
	glPushMatrix();
	glTranslatef(0, radius, -(depth / 2));
	gluCylinder(cylinder, radius, radius, depth, 25, 1);
	glPopMatrix();

	// draw disk1
	glPushMatrix();
	glTranslatef(0, radius, -(depth / 2));
	gluDisk(disk1, 0, radius, 25, 1);
	glPopMatrix();

	// draw disk2
	glPushMatrix();
	glTranslatef(0, radius, (depth / 2));
	gluDisk(disk2, 0, radius, 25, 1);
	glPopMatrix();

}
