#ifndef RCTPRISM_H
#define RCTPRISM_H
#include "Shape.hpp"

namespace RCT {
	class Rectangular_Prism : public Shape {

	protected:
		double x_l;
		double y_l;
		double z_l;
		double vertices[8][3] = { 0 };
		void updateVerticies();
	public:
		Rectangular_Prism();
		Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z);
		Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double _rotation);


		/*void setXLength(double length_x);
		void setYLength(double length_y);
		void setZLength(double length_z);*/

		void draw();



	};

}
#endif 
