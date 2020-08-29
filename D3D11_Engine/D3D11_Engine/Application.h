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

class Scene;

class Application
{
private:
	LARGE_INTEGER beforeInterval, currentInterval, frequency;
	
	//D3D11 Core
	D3D11Graphic* d3d11Graphic;

	//System Manager
	InputManager* inputManager;
	SceneManager* sceneManager;
	HINSTANCE hInstance;
	HWND hWnd;

	Application();
	~Application();

	float getDeltaTime();
	void Render();
	void Update();
public:
	static Application* Instance();
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HWND FloatWindow(HINSTANCE hInstance, int cmdShow);

	void InitializeWindow(HINSTANCE hInstance);
	bool InitializeD3D11(HWND hWnd);
	void InitDeltaTime();

	void ReleaseD3D11();
	void InitializeManager();
	void DeleteManager();

	int DoMainLoop(Scene* firstScene);

	//Get HWND, D3D11Device
	HWND GetHwnd() const;
	ID3D11Device* GetD3D11Device() const;
	ID3D11DeviceContext* GetD3D11DeviceContext() const;

	//Get System Managers
	InputManager* GetInputManager() const;
	SceneManager* GetSceneManager() const;
};