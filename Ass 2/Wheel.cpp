#include "Wheel.h"
#include "Cylinder.h"
#include "Shape.hpp"
#include <iostream>

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
CYL::Wheel::Wheel() :Cylinder() {
	inner_radius = 0.0;
	isRolling = 0;
	isSteering = 0;
	speed = 0.0;
}

// initialise cylinder with given dimensions and default rotation
CYL::Wheel::Wheel(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _red, double _green, double _blue, bool _isRolling, bool _isSteering) :Cylinder(_x, _y, _z, _outer_radius, _depth, _red, _green, _blue) {
	inner_radius = _inner_radius;
	isRolling = _isRolling;
	isSteering = _isSteering;
	speed = 0.0;
}

// initialise cylidner with given dimensions and rotation
CYL::Wheel::Wheel(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _red, double _green, double _blue, double _rotation,  bool _isRolling, bool _isSteering) :Cylinder(_x, _y, _z, _outer_radius, _depth, _red, _green, _blue, _rotation) {
	inner_radius = _inner_radius;
	isRolling = _isRolling;
	isSteering = _isSteering;
	speed = 0.0;
}

// setters for radius and motion states
void CYL::Wheel::setInnerRadius(double _inner_radius) {
	this->inner_radius = _inner_radius;
}

void CYL::Wheel::setIsRolling(double _isRolling) {
	this->isRolling = _isRolling;
}

void CYL::Wheel::setIsSteering(double _isSteering) {
	this->isSteering = _isSteering;
}

void CYL::Wheel::setSpeed(double _speed) {
	this->speed = _speed;
}


// draws the shape
void CYL::Wheel::draw() {
	std::cout << this->getY() << std::endl;
	GLUquadricObj *disk1; // One face of cylinder
	GLUquadricObj *disk2; // Second face of cylinder
	GLUquadricObj *cylinder; // Body of cylinder
	GLUquadricObj *inner_cylinder; // inner body of cylinder, for hollow cylinders

	float x_p = x;
	float y_p = y + outer_radius;
	float z_p = z;

	GLUquadricObj *disk3; // One face of visualiser cylinder
	GLUquadricObj *disk4; // One face of visualiser cylinder
	GLUquadricObj *v_cylinder; // visualiser cylinder


	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();
	cylinder = gluNewQuadric();
	inner_cylinder = gluNewQuadric();

	disk3 = gluNewQuadric();
	disk4 = gluNewQuadric();
	v_cylinder = gluNewQuadric();

	glPushAttrib(GL_CURRENT_BIT);
	int timeElapsed = glutGet(GLUT_ELAPSED_TIME);

	float v_val = (outer_radius - inner_radius) / 3.5;

	// draw cylinder

	this->setColorInGL();
	glPushMatrix();

	//glRotatef(this->rotation, 0, 1, 0);
	this->positionInGL();
	// draw outer cylinder
	glPushMatrix();
	glTranslatef(0, outer_radius, -(depth / 2));
	gluCylinder(cylinder, outer_radius, outer_radius, depth, 25, 1);
	glPopMatrix();

	// draw inner cylinder
	glPushMatrix();
	glTranslatef(0, outer_radius, -(depth / 2));
	gluCylinder(inner_cylinder, inner_radius, inner_radius, depth, 25, 1);
	glPopMatrix();

	// draw disk1
	glPushMatrix();
	glTranslatef(0, outer_radius, -(depth / 2));
	gluDisk(disk1, inner_radius, outer_radius, 25, 1);
	glPopMatrix();

	// draw disk2
	glPushMatrix();
	glTranslatef(0, outer_radius, (depth / 2));
	gluDisk(disk2, inner_radius, outer_radius, 25, 1);
	glPopMatrix();

	// draw rolling visualiser

	glColor3f(red + 0.5, green, blue);

	glPushMatrix();
	glTranslatef(0, v_val, -((depth+0.05)/ 2));
	gluCylinder(v_cylinder, v_val, v_val, depth+0.05, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, v_val, -((depth + 0.05) / 2));
	gluDisk(disk3, 0, v_val, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, v_val, ((depth + 0.05) / 2));
	gluDisk(disk4, 0, v_val , 25, 1);
	glPopMatrix();

	glPopMatrix();

	glPopAttrib();
}
