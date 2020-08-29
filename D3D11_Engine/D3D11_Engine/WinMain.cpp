#include "stdafx.h"
#include "Application.h"
#include "Console.h"
#include "Scene.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, INT cmdShow) {
	srand(GetTickCount());

	Console console;

	if (!D3D11_APP)
		return WM_QUIT;

	if (USE_CONSOLE)
		console.OpenConsole();

	D3D11_APP->InitializeWindow(hInstance);
	D3D11_APP->InitializeD3D11(D3D11_APP->FloatWindow(hInstance, cmdShow));
	D3D11_APP->InitializeManager();
	
	return D3D11_APP->DoMainLoop(new Scene());
}