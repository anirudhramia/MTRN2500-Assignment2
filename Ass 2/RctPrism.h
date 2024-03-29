#ifndef RCTPRISM_H
#define RCTPRISM_H
#include "Shape.hpp"

namespace RCT {
	class Rectangular_Prism : public Shape {
	protected:
		 //lengths in x,y,z direction
		double x_l;
		double y_l;
		double z_l;
		//array of vertex points
		double vertices[8][3] = { 0 };
		//updates the vertex points
		void updateVertices();
	public:
		//Constructors for: no dimensions given, dimensions given, dimensions and rotation given
		Rectangular_Prism();
		Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double _red, double _green, double _blue);
		Rectangular_Prism(double _x, double _y, double _z, double length_x, double length_y, double length_z, double _red, double _green, double _blue, double _rotation);

		//Setters for x,y,z lengths
		void setXLength(double length_x);
		void setYLength(double length_y);
		void setZLength(double length_z);

		//draws the prism
		void draw();



	};

}
#endif 
