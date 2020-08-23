#pragma once
#include <Windows.h>

//Define
#define WINDOW_WIDTH 1280
#define WINDOW_HIEGHT 720
#define USE_CONSOLE true
#define PROGRAM_NAME TEXT("D3D11_Engine")
#define CONSOLE_NAME TEXT("D3D11_Console")

//Initialize D3D11Class, ConsoleClass
#define ENGINE_APP Application::Instance()

class D3D11Graphic;

class Application
{
private:
	LARGE_INTEGER beforeInterval, currentInterval, Frequency;

	Application();
	~Application();
public:
	static Application* Instance();

	void InitWindow(HINSTANCE hInstance);
	void InitD3D11();
};

