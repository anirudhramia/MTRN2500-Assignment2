
#include "Vehicle.hpp"
#include "Cylinder.h"
#include "TrapPrism.h"
#include "TriPrism.h"
#include "RctPrism.h"

Vehicle::Vehicle() :Shape() {
	speed = steering = 0;
	RCT::Rectangular_Prism * rectangle = new RCT::Rectangular_Prism(x, y, z, 3, 1, 2, rotation);
	RCT::Rectangular_Prism * rectangle2 = new RCT::Rectangular_Prism(x, y + 1, z, 1, 1, 1, rotation);
	CYL::Cylinder * cylinder = new CYL::Cylinder(x + 1, y - 0.5, z, 0.3, 0.5, 2.2, rotation);
	CYL::Cylinder * cylinder2 = new CYL::Cylinder(x + 1, y - 0.3, z, 0, 0.3, 2.1, rotation);
	CYL::Cylinder * cylinder3 = new CYL::Cylinder(x - 1, y - 0.5, z, 0.3, 0.5, 2.2, rotation);
	CYL::Cylinder * cylinder4 = new CYL::Cylinder(x - 1, y - 0.3, z, 0, 0.3, 2.1, rotation);
	TRI::Triangular_Prism * triangle = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, rotation + 180);
	TPZ::Trapezoidal_Prism * trapezium = new TPZ::Trapezoidal_Prism(x + 1, y + 1, z, 0.5, 0.3, 0.5, 0.1, 0.01, rotation +90);
	rectangle->setColor(0.75, 0, 0);
	rectangle2->setColor(0.75, 0.25, 0.25);
	cylinder->setColor(0.05, 0.05, 0.05);
	cylinder2->setColor(0.75, 0.75, 0.75);
	cylinder3->setColor(0.05, 0.05, 0.05);
	cylinder4->setColor(0.75, 0.75, 0.75);
	triangle->setColor(1, 0.5, 0);
	trapezium->setColor(0.5, 0.5, 0.5);
	addShape(rectangle);
	addShape(rectangle2);
	addShape(cylinder);
	addShape(cylinder2);
	addShape(cylinder3);
	addShape(cylinder4);
	addShape(triangle);
	addShape(trapezium);
	


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

