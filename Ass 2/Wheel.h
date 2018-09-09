#ifndef  WHEEL_H
#define WHEEL_H

#include "Cylinder.h"

namespace CYL {

	class Wheel : public Cylinder {

	protected:
		bool isRolling;
		bool isSteering;
		double inner_radius;
		double speed;
		double angle;

	public:
		Wheel();
		Wheel(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _red, double _green, double _blue, bool _isRolling, bool _isSteering);
		Wheel(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _red, double _green, double _blue, double _rotation, bool _isRolling, bool _isSteering);

		void setInnerRadius(double _inner_radius);
		void setIsRolling(double _isRolling);
		void setIsSteering(double _isSteering);
		void setSpeed(double _speed);

		void draw();
	};

}

#endif // ! WHEEL_H
