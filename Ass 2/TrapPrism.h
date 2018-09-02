#ifndef TRAPPRISM_H
#define TRAPPRISM_H
#include "Shape.hpp"

namespace TPZ {
	class Trapezoidal_Prism : public Shape {
	protected:
		// dimensions of shape
		double x_l;
		double y_l;
		double z_l;

		// offset of the slanted sides from each end
		double l_off;
		double r_off;

		// array of vertex points
		double vertices[8][3] = { 0 };

		// updates the vertex points
		void updateVertices();

	public:
		// Constructors for: no dimensions given, dimensions given, dimensions and rotation given
		Trapezoidal_Prism();
		Trapezoidal_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double left_offset, double right_offset, double _red, double _green, double _blue);
		Trapezoidal_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double left_offset, double right_offset, double _red, double _green, double _blue, double _rotation);

		// setters for shape dimensions
		void setXLength(double length_x);
		void setYLength(double length_y);
		void setZLength(double length_z);
		void setLeftOffset(double _left_offset);
		void setRightOffset(double _right_offset);

		// draw function
		void draw();

	};



}

#endif

