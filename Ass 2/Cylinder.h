#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.hpp"

namespace CYL {
	class Cylinder : public Shape {

	protected:
		double radius;
		double depth;

		//void updateVerticies();

	public:
		Cylinder();
		Cylinder(double _x, double _y, double _z, double radius, double depth);
		Cylinder(double _x, double _y, double _z, double radius, double depth, double _rotation);


		/*void setXLength(double length_x);
		void setYLength(double length_y);
		void setZLength(double length_z);*/

		void draw();



	};

}
#endif 

