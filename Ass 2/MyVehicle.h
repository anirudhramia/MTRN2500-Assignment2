#ifndef  MYVEHICLE_H
#define MYVEHICLE_h

#include "Vehicle.hpp"
#include <iostream>
#include "Shape.hpp"
#include "Cylinder.h"
#include "TrapPrism.h"
#include "TriPrism.h"
#include "RctPrism.h"
#include "Wheel.h"
#include "VectorMaths.hpp"
#include "Messages.hpp"
#include <vector>

class MyVehicle : public Vehicle {
public:
	MyVehicle();
	MyVehicle(VehicleModel vm);

	void draw();
protected:
	VehicleModel Model;
};

#endif 

