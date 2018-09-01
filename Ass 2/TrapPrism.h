#ifndef TRAPPRISM_H
#define TRAPPRISM_H
#include "Shape.hpp"

namespace TPZ {
	class Trapezoidal_Prism : public Shape {
	protected:
		double x_l;
		double y_l;
		double z_l;
		double l_off;
		double r_off;
		double vertices[8][3] = { 0 };

		void updateVertices();

	public:
		Trapezoidal_Prism();
		Trapezoidal_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double left_offset, double right_offset);
		Trapezoidal_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double left_offset, double right_offset, double _rotation);

		//void setXLength(double length_x);
		//void setSlantLength(double length_slant);
		//void setZLength(double length_z);
		//void setAngle(double _angle);

		void draw();

	};



}

#endif

