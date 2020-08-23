#pragma once
#include "Math.h"

#define KEY_DOWN 2
#define KEY_ON 1
#define KEY_UP 0
#define KEY_NONE -1

class InputManager
{
private:
	bool lastKeys[256];
	bool currentKeys[256];
	POINT cursorPos;

public:
	InputManager();
	~InputManager();

	void UpdateKeyState();
	int GetCurrentKeyState(int vk);
	Vec2 GetMousePos();
	Vec2 GetWorldMousePos();
};

