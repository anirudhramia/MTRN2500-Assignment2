#include "MyVehicle.h"



MyVehicle::MyVehicle():Vehicle(){
	// initialise shapes to add onto car 
	RCT::Rectangular_Prism * bot_body = new RCT::Rectangular_Prism(x, y, z, 3, 1, 2, 0.75, 0, 0, rotation);
	TPZ::Trapezoidal_Prism * top_body = new TPZ::Trapezoidal_Prism(x - 0.25, y + 1, z, 1.5, 0.75, 2, 0.4, 0.05, 0, 0.5, 0.75, rotation);
	CYL::Cylinder * front_tyre = new CYL::Cylinder(x + 1, y - 0.5, z, 0.2, 0.5, 2.2, 0.05, 0.05, 0.05, rotation);
	CYL::Cylinder * front_rim = new CYL::Cylinder(x + 1, y - 0.2, z, 0, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	CYL::Cylinder * back_tyre = new CYL::Cylinder(x - 1, y - 0.5, z, 0.2, 0.5, 2.2, 0.05, 0.05, 0.05, rotation);
	CYL::Cylinder * back_rim = new CYL::Cylinder(x - 1, y - 0.2, z, 0, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	TRI::Triangular_Prism * spoiler = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, 1, 0.5, 0, rotation + 180);
	TPZ::Trapezoidal_Prism * engine = new TPZ::Trapezoidal_Prism(x + 1, y + 1, z, 0.5, 0.3, 0.5, 0.1, 0.01, 0.5, 0.5, 0.5, rotation + 90);

	// add shapes onto shape array for drawing
	addShape(bot_body);
	addShape(top_body);
	addShape(front_tyre);
	addShape(front_rim);
	addShape(back_tyre);
	addShape(back_rim);
	addShape(spoiler);
	addShape(engine);

}

void MyVehicle::draw(){
	
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw();
	}

}
