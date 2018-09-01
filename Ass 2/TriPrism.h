#ifndef TRIPRISM_H
#define TRIPRISM_H
#include "Shape.hpp"

namespace TRI {
	class Triangular_Prism : public Shape {
	protected:
		double x_l;
		double slant_l;
		double z_l;
		double angle;
		double vertices[6][3] = { 0 };

		void updateVertices();

	public:
		Triangular_Prism();
		Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle);
		Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle, double _rotation);

		void setXLength(double length_x);
		void setSlantLength(double length_slant);
		void setZLength(double length_z);
		void setAngle(double _angle);

		void draw();

	};



}

#endif
