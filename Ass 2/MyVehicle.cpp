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
	CYL::Wheel * back_left_tyre = new CYL::Wheel(x - 1, y - 0.5, z - 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1,1);
	CYL::Wheel * back_right_tyre = new CYL::Wheel(x - 1, y - 0.5, z + 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1, 1);
	CYL::Cylinder * back_axle = new CYL::Cylinder(x - 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	TRI::Triangular_Prism * spoiler = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, 1, 0.5, 0, rotation + 180);
	TPZ::Trapezoidal_Prism * engine = new TPZ::Trapezoidal_Prism(x + 1, y + 1, z, 0.5, 0.3, 0.5, 0.1, 0.1, 0.5, 0.5, 0.5, rotation + 90);

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
	for (int i = 0; i < vm.shapes.size(); i++) {
	
		switch (vm.shapes[i].type)
		{
		case RECTANGULAR_PRISM:
			addShape(new RCT::Rectangular_Prism(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].params.rect.xlen, vm.shapes[i].params.rect.ylen, vm.shapes[i].params.rect.zlen, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].rotation)); 
			break;
		case TRIANGULAR_PRISM:
			addShape(new TRI::Triangular_Prism(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].params.tri.alen, vm.shapes[i].params.tri.blen, vm.shapes[i].params.tri.depth, vm.shapes[i].params.tri.angle, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].rotation));
			break;
		case TRAPEZOIDAL_PRISM:
			addShape(new TPZ::Trapezoidal_Prism(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].params.trap.alen, vm.shapes[i].params.trap.height, vm.shapes[i].params.trap.depth, vm.shapes[i].params.trap.aoff, (vm.shapes[i].params.trap.alen - vm.shapes[i].params.trap.blen - vm.shapes[i].params.trap.aoff), vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].rotation));
			break;
		case CYLINDER:
			if (!vm.shapes[i].params.cyl.isRolling) {
				addShape(new CYL::Cylinder(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].rotation));
			}
			else {
				addShape(new CYL::Wheel(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], 0, vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].params.cyl.isRolling, vm.shapes[i].params.cyl.isSteering));
			}
			break;
			
		default:
			break;
		}

		this->Model = vm;

		//RCT::Rectangular_Prism * mid_body = new RCT::Rectangular_Prism(x, y + 0.5, z, 3.25, 0.5, 2, 0.75, 0, 0, rotation);
		//RCT::Rectangular_Prism * bot_body = new RCT::Rectangular_Prism(x, y - 0.25, z, 3.25, 1, 1.45, 0.75, 0, 0, rotation);
		//RCT::Rectangular_Prism * side_body = new RCT::Rectangular_Prism(x, y - 0.25, z, 1, 1, 2, 0.75, 0, 0, rotation);
		//TPZ::Trapezoidal_Prism * top_body = new TPZ::Trapezoidal_Prism(x - 0.25, y + 1, z, 1.5, 0.75, 2, 0.4, 0.05, 0, 0.5, 0.75, rotation);
		//CYL::Wheel * front_left_tyre = new CYL::Wheel(x + 1, y - 0.5, z - 1, 0.2, 0.5, 0.4, 0.05, 0.05, 0.05, rotation, 1, 1);
		//CYL::Wheel * front_right_tyre = new CYL::Wheel(x + 1, y - 0.5, z + 1, 0.2, 0.5, 0.4, 0.05, 0.05, 0.05, rotation, 1, 1);
		//CYL::Cylinder * front_axle = new CYL::Cylinder(x + 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
		//CYL::Wheel * back_left_tyre = new CYL::Wheel(x - 1, y - 0.5, z - 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1, 1);
		//CYL::Wheel * back_right_tyre = new CYL::Wheel(x - 1, y - 0.5, z + 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1, 1);
		//CYL::Cylinder * back_axle = new CYL::Cylinder(x - 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
		//TRI::Triangular_Prism * spoiler = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, 1, 0.5, 0, rotation + 180);
		//TPZ::Trapezoidal_Prism * engine = new TPZ::Trapezoidal_Prism(x + 1, y + 1, z, 0.5, 0.3, 0.5, 0.1, 0.1, 0.5, 0.5, 0.5, rotation + 90);

		//// add shapes onto shape array for drawing
		//addShape(mid_body);
		//addShape(bot_body);
		//addShape(side_body);
		//addShape(top_body);
		//addShape(front_left_tyre);
		//addShape(front_right_tyre);
		//addShape(front_axle);
		//addShape(back_left_tyre);
		//addShape(back_right_tyre);
		//addShape(back_axle);
		//addShape(spoiler);
		//addShape(engine);

	}
}

void MyVehicle::draw(){
	glPushMatrix();


	this->positionInGL();
	for (int i = 0; i < shapes.size(); i++) {
		if (this != NULL && this->Model.shapes.size() != 0 &&  this->Model.shapes[i].type == CYLINDER && this->Model.shapes[i].params.cyl.isSteering) {
			shapes[i]->setRotation(steering);
		}
		shapes[i]->draw();
	}
	glPopMatrix();
}
