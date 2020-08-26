#include "stdafx.h"
#include "Application.h"
#include "Console.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, INT cmdShow) {
	srand(GetTickCount());

	Console console;

	if (USE_CONSOLE)
		console.OpenConsole();

	D3D11_APP->InitWindow(hInstance);
	D3D11_APP->InitD3D11(D3D11_APP->FloatWindow(hInstance, cmdShow));
}