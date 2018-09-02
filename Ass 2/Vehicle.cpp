
#include "Vehicle.hpp"
#include "Cylinder.h"
#include "TrapPrism.h"
#include "TriPrism.h"
#include "RctPrism.h"

// constructor for vehicle
Vehicle::Vehicle() :Shape() {
	speed = steering = 0;
	// initialise shapes to add onto car 
	RCT::Rectangular_Prism * bot_body = new RCT::Rectangular_Prism(x, y, z, 3, 1, 2, 0.75, 0, 0, rotation);
	TPZ::Trapezoidal_Prism * top_body = new TPZ::Trapezoidal_Prism(x-0.25, y + 1, z, 1.5, 0.75, 2, 0.4, 0.05, 0, 0.5, 0.75, rotation);
	CYL::Cylinder * front_tyre = new CYL::Cylinder(x + 1, y - 0.5, z, 0.2, 0.5, 2.2, 0.05, 0.05, 0.05, rotation);
	CYL::Cylinder * front_rim = new CYL::Cylinder(x + 1, y - 0.2, z, 0, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	CYL::Cylinder * back_tyre = new CYL::Cylinder(x - 1, y - 0.5, z, 0.2, 0.5, 2.2, 0.05, 0.05, 0.05, rotation);
	CYL::Cylinder * back_rim = new CYL::Cylinder(x - 1, y - 0.2, z, 0, 0.2, 2.1, 0.75, 0.75, 0.75,  rotation);
	TRI::Triangular_Prism * spoiler = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, 1, 0.5, 0, rotation + 180);
	TPZ::Trapezoidal_Prism * engine = new TPZ::Trapezoidal_Prism(x + 1, y + 1, z, 0.5, 0.3, 0.5, 0.1, 0.01, 0.5, 0.5, 0.5, rotation +90);

	// add shapes onto shape array for drawing
	addShape(bot_body);
	addShape(top_body);
	addShape(front_tyre);
	addShape(front_rim);
	addShape(back_tyre);
	addShape(back_rim);
	addShape(spoiler);
	addShape(engine);
	


};

Vehicle::~Vehicle()
{ 
	// clean-up added shapes
	for(int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}

}

void Vehicle::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if(fabs(speed) < .1)
		speed = 0;
	if(fabs(steering) < .1)
		steering = 0;

}

void Vehicle::update(double speed_, double steering_, double dt) 
{
	speed = speed + ((speed_) - speed)*dt*4;
	steering = steering + (steering_ - steering)*dt * 6;

	update(dt);
}

void Vehicle::draw(){
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw();
	}
}

void Vehicle::addShape(Shape * shape) 
{
	shapes.push_back(shape);
}

double clamp(double a, double n, double b) {

	if (a < b) {
		if (n < a) n = a;
		if (n > b) n = b;
	} else {
		if (n < b) n = b;
		if (n > a) n = a;
	}

	return n;

};

