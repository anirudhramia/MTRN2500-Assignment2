#include "VhclToShp.h"



VehicleModel defaultModel()
{
	int x = 0;
	int y = static_cast<int>(0.25);
	int z = 0;
	VehicleModel vmBase;
	vmBase.remoteID = 0;
	ShapeInit ShapeStruct;
	//Mid body
	ShapeStruct.xyz[0] = static_cast<float>(x);
	ShapeStruct.xyz[1] = static_cast<float>(y+0.5);
	ShapeStruct.xyz[2] = static_cast<float>(z);
	ShapeStruct.type = RECTANGULAR_PRISM;
	ShapeStruct.params.rect = { static_cast<float>(3.25), static_cast<float>(0.5), 2 };
	ShapeStruct.rgb[0] = 0.75;
	ShapeStruct.rgb[1] = 0;
	ShapeStruct.rgb[2] = 0;
	ShapeStruct.rotation = 0;
	vmBase.shapes.push_back(ShapeStruct);

	//Bot Body
	ShapeStruct.xyz[1] = static_cast<float>(y-0.25);
	ShapeStruct.params.rect = { static_cast<float>(3.25), 1, static_cast<float>(1.45) };
	vmBase.shapes.push_back(ShapeStruct);

	//Side Body
	ShapeStruct.params.rect = { 1,1,2 };
	vmBase.shapes.push_back(ShapeStruct);

	//Top Body
	ShapeStruct.type = TRAPEZOIDAL_PRISM;
	ShapeStruct.xyz[0] = static_cast<float>(x - 0.25);
	ShapeStruct.xyz[1] = static_cast<float>(y + 1);
	ShapeStruct.params.trap.alen = 1.5;
	ShapeStruct.params.trap.height = 0.75;
	ShapeStruct.params.trap.depth = 2;
	ShapeStruct.params.trap.aoff = static_cast<float>(0.4);
	ShapeStruct.params.trap.blen = static_cast<float>(1.05);
	ShapeStruct.rgb[0] = 0;
	ShapeStruct.rgb[1] = 0.5;
	ShapeStruct.rgb[2] = 0.75;
	vmBase.shapes.push_back(ShapeStruct);

	//Engine
	
	return vmBase;


}

/*	RCT::Rectangular_Prism * mid_body  = new RCT::Rectangular_Prism(x, y + 0.5 , z, 3.25, 0.5, 2   , 0.75, 0, 0, rotation);
	RCT::Rectangular_Prism * bot_body  = new RCT::Rectangular_Prism(x, y - 0.25, z, 3.25, 1  , 1.45, 0.75, 0, 0, rotation);
	RCT::Rectangular_Prism * side_body = new RCT::Rectangular_Prism(x, y - 0.25, z, 1   , 1  , 2   , 0.75, 0, 0, rotation);

	TPZ::Trapezoidal_Prism * top_body = new TPZ::Trapezoidal_Prism(x - 0.25, y + 1, z, 1.5, 0.75, 2  , 0.4, 0.05, 0  , 0.5, 0.75, rotation);
	TPZ::Trapezoidal_Prism * engine   = new TPZ::Trapezoidal_Prism(x + 1   , y + 1, z, 0.5, 0.3 , 0.5, 0.1, 0.1 , 0.5, 0.5, 0.5 , rotation + 90);

	CYL::Wheel * front_left_tyre  = new CYL::Wheel(x + 1, y - 0.5, z - 1, 0.2, 0.5, 0.4, 0.05, 0.05, 0.05, rotation, 1, 1);
	CYL::Wheel * front_right_tyre = new CYL::Wheel(x + 1, y - 0.5, z + 1, 0.2, 0.5, 0.4, 0.05, 0.05, 0.05, rotation, 1, 1);
	CYL::Wheel * back_left_tyre   = new CYL::Wheel(x - 1, y - 0.5, z - 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1, 1);
	CYL::Wheel * back_right_tyre  = new CYL::Wheel(x - 1, y - 0.5, z + 1, 0.2, 0.5, 0.5, 0.05, 0.05, 0.05, rotation, 1, 1);

	CYL::Cylinder * front_axle = new CYL::Cylinder(x + 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);
	CYL::Cylinder * back_axle  = new CYL::Cylinder(x - 1, y - 0.2, z, 0.2, 2.1, 0.75, 0.75, 0.75, rotation);

	TRI::Triangular_Prism * spoiler = new TRI::Triangular_Prism(x - 1.25, y + 1, z, 0.2, 0.4, 2, 120, 1, 0.5, 0, rotation + 180);
	*/