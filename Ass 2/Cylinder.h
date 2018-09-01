#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.hpp"

namespace CYL {
	class Cylinder : public Shape {

	protected:
		double _radius;
		double _radius;

		void updateVerticies();

	public:
		Cylinder();
		Cylinder(double _radius, double _depth);
		Cylinder(double _radius, double _depth, double _rotation);


		/*void setXLength(double length_x);
		void setYLength(double length_y);
		void setZLength(double length_z);*/

		void draw();



	};

}
#endif 

