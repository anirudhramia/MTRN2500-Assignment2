#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.hpp"

namespace CYL {
	class Cylinder : public Shape {

	protected:
		// radii of inner and outer radius 
		// inner radius = 0 for disk with no hole in the centre
		//double inner_radius;
		double outer_radius;

		//length of cylinder
		double depth;

	public:
		// constructors for no dimensions, dimensions given and dimensions + rotation given
		Cylinder();
		Cylinder(double _x, double _y, double _z, double _outer_radius, double _depth, double _red, double _green, double _blue);
		Cylinder(double _x, double _y, double _z, double _outer_radius, double _depth, double _red, double _green, double _blue, double _rotation);

		// setters for dimensions
		//void setInnerRadius(double _inner_radius);
		void setOuterRadius(double _outer_radius);
		void setDepth(double _depth);

		// draw function
		void draw();


	};

}
#endif 

