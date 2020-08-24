#pragma once
#include <Windows.h>
#include "Math.h"

//Define
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define USE_CONSOLE true
#define PROGRAM_NAME TEXT("D3D11_Engine")
#define CONSOLE_NAME TEXT("D3D11_Console")
#define BACKGROUND_COLOR Color(0,0,0,0).getColorArray()

//Initialize D3D11Class, ConsoleClass
#define D3D11_APP Application::Instance()

class D3D11Graphic;
class InputManager;
class SceneManager;

class Application
{
private:
	LARGE_INTEGER beforeInterval, currentInterval, frequency;
	D3D11Graphic* d3d11Graphic;
	InputManager* inputManager;
	SceneManager* sceneManager;
	HWND hWnd;

	Application();
	~Application();

	void Update(float dt);
	void Render();
public:
	static Application* Instance();
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HWND FloatWindow(HINSTANCE hInstance, int cmdShow);

	void InitWindow(HINSTANCE hInstance);
	bool InitD3D11(HWND hWnd);
	void InitDeltaTime();

	void ReleseD3D11();
	void DeleteManager();

	int DoMainLoop(Scene* firstScene);
	float getDeltaTime();

	//Get HWND, D3D11Device
	HWND GetHwnd() const;
	ID3D11Device* GetD3D11Device() const;
	ID3D11DeviceContext* GetD3D11DeviceContext() const;

	//Get System Managers
	InputManager* GetInputManager() const;
};