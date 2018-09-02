#ifndef TRIPRISM_H
#define TRIPRISM_H
#include "Shape.hpp"

namespace TRI {
	class Triangular_Prism : public Shape {
	protected:
		// dimensions of shape
		double x_l;
		double slant_l;
		double z_l;
		double angle;

		// array of vertex points
		double vertices[6][3] = { 0 };

		// updates the vertex points
		void updateVertices();

	public:
		//Constructors for: no dimensions given, dimensions given, dimensions and rotation given
		Triangular_Prism();
		Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle, double _red, double _green, double _blue);
		Triangular_Prism(double _x, double _y, double _z, double length_x, double length_slant, double length_z, double _angle, double _red, double _green, double _blue, double _rotation);

		// setters for shape dimensions
		void setXLength(double length_x);
		void setSlantLength(double length_slant);
		void setZLength(double length_z);
		void setAngle(double _angle);

		// draw function
		void draw();

	};



}

#endif
