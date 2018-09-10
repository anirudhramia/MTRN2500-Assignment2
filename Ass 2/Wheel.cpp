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

#define PI 3.14159265358979323846


// initalise cylinder with zero dimensions
CYL::Wheel::Wheel() :Cylinder() {
	inner_radius = 0.0;
	isRolling = 0;
	isSteering = 0;
	speed = 0.0;
	angle = 0.0;
	startTime = 0.0;
}

// initialise cylinder with given dimensions and default rotation
CYL::Wheel::Wheel(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _red, double _green, double _blue, bool _isRolling, bool _isSteering) :Cylinder(_x, _y, _z, _outer_radius, _depth, _red, _green, _blue) {
	inner_radius = _inner_radius;
	isRolling = _isRolling;
	isSteering = _isSteering;
	speed = 0.0;
	angle = 0.0;
	startTime = 0;
}

// initialise cylidner with given dimensions and rotation
CYL::Wheel::Wheel(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _red, double _green, double _blue, double _rotation,  bool _isRolling, bool _isSteering) :Cylinder(_x, _y, _z, _outer_radius, _depth, _red, _green, _blue, _rotation) {
	inner_radius = _inner_radius;
	isRolling = _isRolling;
	isSteering = _isSteering;
	speed = 0.0;
	angle = 0.0;
	startTime = 0;
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
	//std::cout << this->getY() << std::endl;
	GLUquadricObj *disk1; // One face of cylinder
	GLUquadricObj *disk2; // Second face of cylinder
	GLUquadricObj *cylinder; // Body of cylinder
	GLUquadricObj *inner_cylinder; // inner body of cylinder, for hollow cylinders

	GLUquadricObj *disk3;
	GLUquadricObj *disk4;

	float y_p = ((inner_radius + outer_radius)/3)*2;
	float delta_angle = 0;

	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();
	cylinder = gluNewQuadric();
	inner_cylinder = gluNewQuadric();

	disk3 = gluNewQuadric();
	disk4 = gluNewQuadric();

	

	glPushAttrib(GL_CURRENT_BIT);

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


	float timeElapsed = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = timeElapsed - startTime;
	startTime = timeElapsed;

	// draw spokes

	glColor3f(1-red, 1-green, 1-blue);
	delta_angle = ((this->speed)/ outer_radius)*(deltaTime/1000);
	
	//
	glPushMatrix();
	angle = angle+delta_angle;
	if (angle > 360) {
		angle = angle - 360;
	}
	else if (angle < -360) {
		angle = angle + 360;
	}
	glTranslated(0, outer_radius, 0);
	glRotated(-angle, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0,0, (depth/2)+0.01); 
	glVertex3f(0,y_p, (depth / 2) + 0.01);
	glVertex3f(0.03,y_p, (depth / 2) + 0.01);
	glVertex3f(0.03, 0, (depth / 2) + 0.01);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0,0, -(depth / 2) - 0.01);
	glVertex3f(0, y_p, -(depth / 2) - 0.01);
	glVertex3f(0.03, y_p, -(depth / 2) - 0.01);
	glVertex3f(0.03, 0, -(depth / 2) - 0.01);
	glEnd();
	glPopMatrix();
	//

	//
	glPushMatrix();
	angle = angle + delta_angle;
	if (angle > 360) {
		angle = angle - 360;
	}
	else if (angle < -360) {
		angle = angle + 360;
	}

	glTranslated(0, outer_radius, 0);
	glRotated(180, 0, 0, 1);
	glRotated(-angle, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, (depth / 2) + 0.01);
	glVertex3f(0, y_p, (depth / 2) + 0.01);
	glVertex3f(-0.03, y_p, (depth / 2) + 0.01);
	glVertex3f(-0.03, 0, (depth / 2) + 0.01);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, -(depth / 2) - 0.01);
	glVertex3f(0, y_p, -(depth / 2) - 0.01);
	glVertex3f(-0.03, y_p, -(depth / 2) - 0.01);
	glVertex3f(-0.03, 0, -(depth / 2) - 0.01);
	glEnd();
	glPopMatrix();
	//

	//
	glPushMatrix();
	angle = angle + delta_angle;
	if (angle > 360) {
		angle = angle - 360;
	}
	else if (angle < -360) {
		angle = angle + 360;
	}

	glTranslated(0, outer_radius, 0);
	glRotated(90, 0, 0, 1);
	glRotated(-angle, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, (depth / 2) + 0.01);
	glVertex3f(0, y_p, (depth / 2) + 0.01);
	glVertex3f(0.03, y_p, (depth / 2) + 0.01);
	glVertex3f(0.03, 0, (depth / 2) + 0.01);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, -(depth / 2) - 0.01);
	glVertex3f(0, y_p, -(depth / 2) - 0.01);
	glVertex3f(0.03, y_p, -(depth / 2) - 0.01);
	glVertex3f(0.03, 0, -(depth / 2) - 0.01);
	glEnd();
	glPopMatrix();
	//

	//
	glPushMatrix();
	angle = angle + delta_angle;
	if (angle > 360) {
		angle = angle - 360;
	}
	else if (angle < -360) {
		angle = angle + 360;
	}

	glTranslated(0, outer_radius, 0);
	glRotated(-90, 0, 0, 1);
	glRotated(-angle, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, (depth / 2) + 0.01);
	glVertex3f(0, y_p, (depth / 2) + 0.01);
	glVertex3f(-0.03, y_p, (depth / 2) + 0.01);
	glVertex3f(-0.03, 0, (depth / 2) + 0.01);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, -(depth / 2) - 0.01);
	glVertex3f(0, y_p, -(depth / 2) - 0.01);
	glVertex3f(-0.03, y_p, -(depth / 2) - 0.01);
	glVertex3f(-0.03, 0, -(depth / 2) - 0.01);
	glEnd();
	glPopMatrix();
	//

	glPushMatrix();
	glTranslatef(0, outer_radius, -(depth / 2)-0.01);
	gluDisk(disk3, y_p, y_p+0.03, 25, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, outer_radius, (depth / 2)+0.01);
	gluDisk(disk4, y_p, y_p+0.03, 25, 1);
	glPopMatrix();


	glPopMatrix();

	glPopAttrib();
}
