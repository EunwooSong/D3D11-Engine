#include "stdafx.h"
#include "Application.h"
#include "D3D11Graphic.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

//------------------------------------------------------------------------
// Priavate
//------------------------------------------------------------------------
Application::Application()
{
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&frequency);
}

Application::~Application()
{
}

float Application::getDeltaTime()
{
	QueryPerformanceCounter(&currentInterval);
	LONGLONG interval = (currentInterval.QuadPart - beforeInterval.QuadPart);

	float dt = (float)interval / (float)frequency.QuadPart;

	beforeInterval = currentInterval;

	return dt;
}

void Application::Render()
{
	d3d11Graphic->BeginScene(Color(1.0f, 0.5f, 0.5f, 0.5f));

	sceneManager->Render();

	d3d11Graphic->EndScene();
}

void Application::Update()
{
	inputManager->UpdateKeyState();
	sceneManager->Update(getDeltaTime());
}

//------------------------------------------------------------------------
// Public
//------------------------------------------------------------------------
Application* Application::Instance()
{
	static Application* tmp = new Application();
	return tmp;
}

LRESULT Application::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

HWND Application::FloatWindow(HINSTANCE hInstance, int cmdShow)
{
	POINT center = {0, };

	if (FULL_SCREEN) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)WINDOW_WIDTH;
		dmScreenSettings.dmPelsHeight = (unsigned long)WINDOW_HEIGHT;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else {
		//Set Window Pos Center
		center.x = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
		center.y = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_HEIGHT) / 2;
	}

	hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		PROGRAM_NAME,
		PROGRAM_NAME,
		(!FULL_SCREEN) ?
		WS_SYSMENU :								//System Mode : Window
		WS_CLIPSIBLINGS | WS_EX_TOPMOST | WS_POPUP, //System Mode : Full Screen
		center.x,									//Set System Window Pos
		center.y,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, cmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return hWnd;
}

void Application::InitializeWindow(HINSTANCE hInstance)
{
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = PROGRAM_NAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);
}

bool Application::InitializeD3D11(HWND hWnd)
{
	d3d11Graphic = (D3D11Graphic*)_aligned_malloc(sizeof(D3D11Graphic), 16);

	if (!d3d11Graphic->Initialize(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		VSYNC_ENABLE,
		hWnd,
		FULL_SCREEN,
		SCREEN_DEPTH,
		SCREEN_NEAR)) {
		MessageBox(hWnd, L"Could not Initialize D3D11.", L"ERROR", MB_OK);
		return false;
	}

	return true;
}

void Application::InitDeltaTime()
{
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceFrequency(&frequency);
}

void Application::ReleaseD3D11()
{
	if (d3d11Graphic) {
		d3d11Graphic->Dispose();
		_aligned_free(d3d11Graphic);
		d3d11Graphic = nullptr;
	}
}

void Application::InitializeManager()
{
	inputManager = new InputManager();
	sceneManager = new SceneManager();
}

void Application::DeleteManager()
{
	SAFE_DELETE(d3d11Graphic);
	SAFE_DELETE(inputManager);
	SAFE_DELETE(sceneManager);
	//SAFE_DELETE();
}

int Application::DoMainLoop(Scene* firstScene)
{
	InitDeltaTime();

	sceneManager->ChangeScene(firstScene);

	MSG Mes;
	ZeroMemory(&Mes, sizeof(Mes));

	while (Mes.message != WM_QUIT) {
		if (PeekMessage(&Mes, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Mes);
			DispatchMessage(&Mes); 
		}

		//Render Objects
		Render();
		//Update Objects
		Update();
	}

	DeleteManager();
	ReleaseD3D11();

	return (int)Mes.wParam;
}

HWND Application::GetHwnd() const
{
	return hWnd;
}

ID3D11Device* Application::GetD3D11Device() const
{
	return d3d11Graphic->GetD3D11Device();
}

ID3D11DeviceContext* Application::GetD3D11DeviceContext() const
{
	return d3d11Graphic->GetDeviceContext();
}

InputManager* Application::GetInputManager() const
{
	return inputManager;
}

SceneManager* Application::GetSceneManager() const
{
	return sceneManager;
}
