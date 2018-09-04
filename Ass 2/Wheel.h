#ifndef  WHEEL_H
#define WHEEL_H

#include "Cylinder.h"

using namespace CYL;

class Wheel : public Cylinder {

protected:
	bool isRolling;
	bool isSteering;
};



#endif // ! WHEEL_H
