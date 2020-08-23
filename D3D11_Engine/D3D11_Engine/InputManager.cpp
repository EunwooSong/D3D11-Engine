#include "stdafx.h"
#include "InputManager.h"
#include "Application.h"

InputManager::InputManager()
{
	ZeroMemory(currentKeys, sizeof(currentKeys));
	ZeroMemory(lastKeys, sizeof(lastKeys));
}

InputManager::~InputManager()
{
}

void InputManager::UpdateKeyState()
{
	for (int i = 0; i < 256; i++) {
		lastKeys[i] = currentKeys[i];
		currentKeys[i] = GetKeyState(i) & 0x8000;
	}

	GetCursorPos(&cursorPos);
	ScreenToClient(D3D11_APP->GetHwnd(), &cursorPos);
}

int InputManager::GetCurrentKeyState(int vk)
{
	if (currentKeys[vk] && lastKeys[vk]) return KEY_ON;
	else if (currentKeys[vk] && !lastKeys[vk]) return KEY_DOWN;
	else if (!currentKeys[vk] && lastKeys[vk]) return KEY_UP;
	else return KEY_NONE;
}

Vec2 InputManager::GetMousePos()
{
	return Vec2(cursorPos);
}

Vec2 InputManager::GetWorldMousePos()
{
	return Vec2();
}
