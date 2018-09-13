
#include <iostream>
#include <Windows.h>
//#include <Xinput.h>
#include "XboxController.h"
#include "XInputWrapper.h"
#include <math.h>
#include <limits.h>

using namespace std;

//This function creates an instance of the class XBoxController and sets the following variables to the states shown
GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id) {
	this->xinput = xinput;
	this->controllerID = id;
	this->xinput->XInputGetState(controllerID, &(this->state));
	this->deadZoneRadius = 0;
	this->Vibrate(0, 0);
	//cout << this->vibration.wLeftMotorSpeed << endl;
	//Sleep(3000);

}



DWORD GamePad::XBoxController::GetControllerId() {
	//cout << "INSIDE" << this->deadZoneRadius;
	return this->controllerID;
}

bool GamePad::XBoxController::IsConnected() {
	return (this->xinput->XInputGetState(controllerID, &state) == ERROR_SUCCESS);
	//return 1;
}

bool GamePad::XBoxController::PressedA() {

	if (!this->IsConnected())
		return 0;
	int andResult = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedB() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedX() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedY() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedLeftShoulder() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER );
	return (andResult != 0);
}


bool GamePad::XBoxController::PressedRightShoulder() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedLeftDpad() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedRightDpad() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedUpDpad() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedDownDpad() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedStart() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedBack() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedLeftThumb() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedRightThumb() {
	this->IsConnected();
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
	return (andResult != 0);
}

BYTE GamePad::XBoxController::LeftTriggerLocation() {
	this->IsConnected();
	return(this->state.Gamepad.bLeftTrigger);
}

BYTE GamePad::XBoxController::RightTriggerLocation() {
	this->IsConnected();
	//cout << "			" << sizeof(this->state.Gamepad.bRightTrigger) << "THERE" << endl;
	return(this->state.Gamepad.bRightTrigger);
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() {
	this->IsConnected();
	GamePad::Coordinate LeftCoord(modulatePosition(this->state.Gamepad.sThumbLX, this->state.Gamepad.sThumbLY));
	//LeftCoord.SetX(this->modulatePosition(LeftCoord.GetX()));
	//LeftCoord.SetY(this->modulatePosition(LeftCoord.GetY()));
	//modulatePosition(LeftCoord);
	return LeftCoord;
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() {
	this->IsConnected();
	GamePad::Coordinate RightCoord(modulatePosition(this->state.Gamepad.sThumbRX, this->state.Gamepad.sThumbRY));

	//RightCoord.SetX(this->modulatePosition(RightCoord.GetX()));
	//RightCoord.SetY(this->modulatePosition(RightCoord.GetY()));
	return RightCoord;
}

void GamePad::XBoxController::Vibrate(WORD left, WORD right) {
	this->IsConnected();
	this->vibration.wLeftMotorSpeed = left;
	this->vibration.wRightMotorSpeed = right;
	this->xinput->XInputSetState(this->controllerID, &(this->vibration));

}

void GamePad::XBoxController::SetDeadzone(unsigned int radius) {
	this->deadZoneRadius = radius;
}

GamePad::Coordinate GamePad::XBoxController::modulatePosition(short xIn, short yIn){
	short xOut = 0;
	short yOut = 0;
	double rad = this->deadZoneRadius;
	double magnitude = sqrt(xOut * xOut + yOut * yOut);
	//cout << "*" <<  magnitude << "*";
	//cout << "&" << this->deadZoneRadius << "&";
	if (magnitude > this->deadZoneRadius) {
		double fraction = ((magnitude - rad) / (double(SHRT_MAX) - rad));
		double scaleFactor = fraction * (double(SHRT_MAX) / magnitude);
		//cout << "	$" << fraction << " " <<scaleFactor << "$	" ;
		xOut = xIn * fabs(scaleFactor);
		yOut = yIn * fabs(scaleFactor);
	}
	else {
		cout << "HERE" << endl;
	}
	GamePad::Coordinate coord(xOut,yOut);
	return coord;
}

//void GamePad::XBoxController::modulatePosition(GamePad::Coordinate &input) {
//	
//	short x = input.GetX();
//	short y = input.GetY();
//	unsigned int magnitude = sqrt(x * x + y * y);
//	if (magnitude <= this->deadZoneRadius) {
//		input.SetX(0);
//		input.SetY(0);
//	}
//	float scaleFactor = (magnitude - (this->deadZoneRadius)) / (SHRT_MAX - (this->deadZoneRadius)) *(SHRT_MAX / magnitude);
//	input.SetX(scaleFactor*x);
//	input.SetY(scaleFactor*y);
//
//	//if ((abs(coordinate)) <= int(this->deadZoneRadius)) {
//	//	return (SHORT(0));
//	//}else {
//	//	float grad = (float(SHRT_MAX) / float(SHRT_MAX - this->deadZoneRadius));
//	//	float yIntercept;
//	//	//cout << "%%" << grad;
//	//	if (coordinate > 0) {
//	//		yIntercept = -grad*(this->deadZoneRadius);
//	//	}else {
//	//		yIntercept = grad*(this->deadZoneRadius);
//	//	}
//	//	SHORT modulatedCoord = grad * coordinate + yIntercept;
//	//	//cout << "*" << coordinate << "*" << modulatedCoord;
//	//	return (modulatedCoord);
//	//}
//	//return 0;
//	
//}