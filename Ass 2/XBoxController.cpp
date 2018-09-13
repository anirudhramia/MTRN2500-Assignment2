
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#include "XboxController.h"
#include "XInputWrapper.h"
#include <math.h>
#include <limits.h>

using namespace std;
GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id) {
	this->xinput = xinput;
	this->controllerID = id;

}



DWORD GamePad::XBoxController::GetControllerId() {
	//cout << "INSIDE" << this->deadZoneRadius;
	return this->controllerID;
}

bool GamePad::XBoxController::IsConnected() {
	return (XInputGetState(controllerID, &state) == ERROR_SUCCESS);
}

bool GamePad::XBoxController::PressedA() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedB() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedX() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedY() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedLeftShoulder() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER );
	return (andResult != 0);
}


bool GamePad::XBoxController::PressedRightShoulder() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedLeftDpad() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedRightDpad() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedUpDpad() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedDownDpad() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedStart() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedBack() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedLeftThumb() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	return (andResult != 0);
}

bool GamePad::XBoxController::PressedRightThumb() {
	int andResult = (this->state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
	return (andResult != 0);
}

BYTE GamePad::XBoxController::LeftTriggerLocation() {
	return(this->state.Gamepad.bLeftTrigger);
}

BYTE GamePad::XBoxController::RightTriggerLocation() {
	//cout << "			" << sizeof(this->state.Gamepad.bRightTrigger) << "THERE" << endl;
	return(this->state.Gamepad.bRightTrigger);
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() {
	GamePad::Coordinate LeftCoord(this->state.Gamepad.sThumbLX, this->state.Gamepad.sThumbLY);
	LeftCoord.SetX(this->modulatePosition(LeftCoord.GetX()));
	LeftCoord.SetY(this->modulatePosition(LeftCoord.GetY()));
	return LeftCoord;
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() {
	GamePad::Coordinate RightCoord(this->state.Gamepad.sThumbRX, this->state.Gamepad.sThumbRY);
	RightCoord.SetX(this->modulatePosition(RightCoord.GetX()));
	RightCoord.SetY(this->modulatePosition(RightCoord.GetY()));
	return RightCoord;
}

void GamePad::XBoxController::Vibrate(WORD left, WORD right) {
	this->vibration.wLeftMotorSpeed = left;
	this->vibration.wRightMotorSpeed = right;
	this->xinput->XInputSetState(this->controllerID, &(this->vibration));

}

void GamePad::XBoxController::SetDeadzone(unsigned int radius) {
	this->deadZoneRadius = radius;
}

SHORT GamePad::XBoxController::modulatePosition(SHORT coordinate) {
	if ((abs(coordinate)) <= int(this->deadZoneRadius)) {
		return (SHORT(0));
	}else {
		float grad = (float(SHRT_MAX) / float(SHRT_MAX - this->deadZoneRadius));
		float yIntercept;
		//cout << "%%" << grad;
		if (coordinate > 0) {
			yIntercept = -grad*(this->deadZoneRadius);
		}else {
			yIntercept = grad*(this->deadZoneRadius);
		}
		SHORT modulatedCoord = grad * coordinate + yIntercept;
		//cout << "*" << coordinate << "*" << modulatedCoord;
		return (modulatedCoord);
	}
	return 0;
	
}