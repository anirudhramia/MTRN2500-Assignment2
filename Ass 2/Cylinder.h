#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.hpp"

namespace CYL {
	class Cylinder : public Shape {

	protected:
		double inner_radius;
		double outer_radius;
		double depth;

		//void updateVerticies();

	public:
		Cylinder();
		Cylinder(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth);
		Cylinder(double _x, double _y, double _z, double _inner_radius, double _outer_radius, double _depth, double _rotation);

		void setInnerRadius(double _inner_radius);
		void setOuterRadius(double _outer_radius);
		void setDepth(double _depth);

		void draw();



	};

}
#endif 

