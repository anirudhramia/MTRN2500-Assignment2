#include "MyVehicle.h"

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


MyVehicle::MyVehicle():Vehicle(){
	// initialise shapes to add onto car 
	this->setY(0.25);
	RCT::Rectangular_Prism * mid_body = new RCT::Rectangular_Prism(x, y + 0.5, z, 3.25, 0.5, 2, 0.75, 0, 0, rotation);
	RCT::Rectangular_Prism * bot_body = new RCT::Rectangular_Prism(x, y - 0.25, z, 3.25, 1, 1.45, 0.75, 0, 0, rotation);
	RCT::Rectangular_Prism * side_body = new RCT::Rectangular_Prism(x, y - 0.25, z, 1, 1, 2, 0.75, 0, 0, rotation);
	TPZ::Trapezoidal_Prism * top_body = new TPZ::Trapezoidal_Prism(x - 0.25, y + 1, z, 1.5, 0.75, 2, 0.4, 0.05, 0, 0.5, 0.75, rotation);
	CYL::Wheel * front_left_tyre = new CYL::Wheel(x + 1, y - 0.5, z - 1, 0.2, 0.5, 0.4, 0.05, 0.05, 0.05, rotation, 1, 1);
	CYL::Wheel * front_right_tyre = new CYL::Wheel(x + 1, y - 0.5, z + 1, 0.2, 0.5, 0.4, 0.05, 0.05, 0.05, rotation, 1, 1);
	CYL::Cylinder * front_axle = new CYL::Cylinder(x + 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	CYL::Wheel * back_left_tyre = new CYL::Wheel(x - 1, y - 0.5, z - 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1,0);
	CYL::Wheel * back_right_tyre = new CYL::Wheel(x - 1, y - 0.5, z + 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1, 0);
	CYL::Cylinder * back_axle = new CYL::Cylinder(x - 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	TRI::Triangular_Prism * spoiler = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, 1, 0.5, 0, rotation);
	TPZ::Trapezoidal_Prism * engine = new TPZ::Trapezoidal_Prism(x + 1, y + 1, z, 0.5, 0.3, 0.5, 0.1, 0.1, 0.5, 0.5, 0.5, rotation);

	// add shapes onto shape array for drawing
	addShape(mid_body);
	addShape(bot_body);
	addShape(side_body);
	addShape(top_body);
	addShape(front_left_tyre);
	addShape(front_right_tyre);
	addShape(front_axle);
	addShape(back_left_tyre);
	addShape(back_right_tyre);
	addShape(back_axle);
	addShape(spoiler);
	addShape(engine);

}

MyVehicle::MyVehicle(VehicleModel vm){
	// make an iterator to go through the vector
	std::vector<ShapeInit>::iterator it;
	for (it = vm.shapes.begin(); it != vm.shapes.end(); it++) {
	
		// for each shape type in the vehicle model, add a shape from local shape classes
		switch (it->type)
		{
		case RECTANGULAR_PRISM:
			addShape(new RCT::Rectangular_Prism(it->xyz[0], it->xyz[1], it->xyz[2], it->params.rect.xlen, it->params.rect.ylen, it->params.rect.zlen, it->rgb[0], it->rgb[1], it->rgb[2], it->rotation)); 
			break;
		case TRIANGULAR_PRISM:
			addShape(new TRI::Triangular_Prism(it->xyz[0], it->xyz[1], it->xyz[2], it->params.tri.alen, it->params.tri.blen, it->params.tri.depth, it->params.tri.angle, it->rgb[0], it->rgb[1], it->rgb[2], it->rotation+180));
			break;
		case TRAPEZOIDAL_PRISM:
			addShape(new TPZ::Trapezoidal_Prism(it->xyz[0], it->xyz[1], it->xyz[2], it->params.trap.alen, it->params.trap.height, it->params.trap.depth, it->params.trap.aoff, (it->params.trap.alen - it->params.trap.blen - it->params.trap.aoff), it->rgb[0], it->rgb[1], it->rgb[2], it->rotation+180));
			break;
		case CYLINDER:
			if (!it->params.cyl.isRolling) {
				addShape(new CYL::Cylinder(it->xyz[0], it->xyz[1], it->xyz[2], it->params.cyl.radius, it->params.cyl.depth, it->rgb[0], it->rgb[1], it->rgb[2], it->rotation));
			}
			else {
				addShape(new CYL::Wheel(it->xyz[0], it->xyz[1], it->xyz[2], 0, it->params.cyl.radius, it->params.cyl.depth, it->rgb[0], it->rgb[1], it->rgb[2], it->params.cyl.isRolling, it->params.cyl.isSteering));
			}
			break;
			
		default:
			break;
		}

		// set this vehicle model variable to vm for draw
		this->Model = vm;

	}
}

void MyVehicle::draw(){
	glPushMatrix();
	// draws shape
	this->positionInGL();
	this->setY(0.25);
	for (int i = 0; i < shapes.size(); i++) {
		// checks if wheel should steer, and updates wheel rotation
		if (this != NULL && this->Model.shapes.size() != 0 && this->Model.shapes[i].type == CYLINDER && this->Model.shapes[i].params.cyl.isSteering) {
			shapes[i]->setRotation(steering);
		}
		// checks if wheel should roll, and updates current speed
		if (this != NULL && this->Model.shapes.size() != 0 && this->Model.shapes[i].type == CYLINDER && this->Model.shapes[i].params.cyl.isRolling) {
			static_cast<CYL::Wheel*>(shapes[i])->setSpeed(speed);
		}
		shapes[i]->draw();
	}

	glPopMatrix();
}
