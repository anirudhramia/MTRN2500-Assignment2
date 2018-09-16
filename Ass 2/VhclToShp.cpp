

#include "VhclToShp.h"



VehicleModel defaultModel()
{
	float x = 0;
	float y = static_cast<float>(0.25);
	float z = 0;
	VehicleModel vmBase;
	vmBase.remoteID = 21;
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
	ShapeStruct.rotation = 180;
	vmBase.shapes.push_back(ShapeStruct);

	//Engine
	ShapeStruct.rotation = 0;
	ShapeStruct.xyz[0] = x + 1;
	ShapeStruct.params.trap.alen = 0.5;
	ShapeStruct.params.trap.height = 0.3;
	ShapeStruct.params.trap.depth = 0.5;
	ShapeStruct.params.trap.aoff = 0.1;
	ShapeStruct.params.trap.blen = 0.3;
	ShapeStruct.rgb[0] = 0.5;
	ShapeStruct.rgb[1] = 0.5;
	ShapeStruct.rgb[2] = 0.5;
	vmBase.shapes.push_back(ShapeStruct);

	//Front left wheel	
	ShapeStruct.rotation = 0;
	ShapeStruct.type = CYLINDER;
	ShapeStruct.xyz[0] = x + 1;
	ShapeStruct.xyz[1] = y - 0.5;
	ShapeStruct.xyz[2] = z - 1;
	ShapeStruct.params.cyl.radius = 0.5;
	ShapeStruct.params.cyl.depth = 0.4;
	ShapeStruct.params.cyl.isRolling = 1;
	ShapeStruct.params.cyl.isSteering = 1;
	ShapeStruct.rgb[0] = 0.05;
	ShapeStruct.rgb[1] = 0.05;
	ShapeStruct.rgb[2] = 0.05;
	vmBase.shapes.push_back(ShapeStruct);

	//Front right Wheel
	ShapeStruct.xyz[2] = z + 1;
	vmBase.shapes.push_back(ShapeStruct);

	//Back left wheel
	ShapeStruct.xyz[0] = x - 1;
	ShapeStruct.xyz[2] = z - 1;
	ShapeStruct.params.cyl.isSteering = 0;
	ShapeStruct.params.cyl.depth = 0.5;
	vmBase.shapes.push_back(ShapeStruct);

	//Back right wheel
	ShapeStruct.xyz[2] = z + 1;
	vmBase.shapes.push_back(ShapeStruct);

	//Spoiler
	ShapeStruct.type = TRIANGULAR_PRISM;
	ShapeStruct.xyz[0] = x - 1.25;
	ShapeStruct.xyz[1] = y + 1;
	ShapeStruct.xyz[2] = z;
	ShapeStruct.params.tri.alen = 0.2;
	ShapeStruct.params.tri.blen = 0.4;
	ShapeStruct.params.tri.depth = 2;
	ShapeStruct.params.tri.angle = 90;
	ShapeStruct.rgb[0] = 1;
	ShapeStruct.rgb[1] = 0.5;
	ShapeStruct.rgb[2] = 0;
	//ShapeStruct.rotation = 180;
	vmBase.shapes.push_back(ShapeStruct);

	return vmBase;


}
