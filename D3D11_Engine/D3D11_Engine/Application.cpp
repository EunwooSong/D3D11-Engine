#include "stdafx.h"
#include "Application.h"
#include "D3D11Graphic.h"

Application::Application()
{
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&frequency);
}

Application::~Application()
{
}

void Application::Update(float dt)
{


}

void Application::Render()
{
	d3d11Graphic->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	//if(currentScene)
	//	currentScene->Render();

	d3d11Graphic->EndScene();
}

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
	hWnd = CreateWindow(
		PROGRAM_NAME,
		PROGRAM_NAME,
		WS_SYSMENU, //<- 창모드
		//WS_EX_TOPMOST | WS_POPUP, // <- 전체화면
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, cmdShow);
	return hWnd;
}

void Application::InitWindow(HINSTANCE hInstance)
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

bool Application::InitD3D11(HWND hWnd)
{
	d3d11Graphic = (D3D11Graphic*)_aligned_malloc(sizeof(D3D11Graphic), 16);

	if (!d3d11Graphic->Initialize(WINDOW_WIDTH,
		WINDOW_HEIGHT,
		VSYNC_ENABLE,
		hWnd,
		FULL_SCREEN,
		SCREEN_DEPTH,
		SCREEN_NEAR)) {
		MessageBox(hWnd, L"Could not initialize D3D11.", L"ERROR", MB_OK);
		return false;
	}

	return true;
}

void Application::InitDeltaTime()
{
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceFrequency(&frequency);
}

void Application::ReleseD3D11()
{
	if (d3d11Graphic) {
		d3d11Graphic->Dispose();
		_aligned_free(d3d11Graphic);
		d3d11Graphic = nullptr;
	}
}

void Application::DeleteManager()
{
	SAFE_DELETE(d3d11Graphic);
	//SAFE_DELETE();
}

int Application::DoMainLoop(Scene* firstScene)
{
	return 0; 
}

float Application::getDeltaTime()
{
	//Get Current Time
	QueryPerformanceCounter(&currentInterval);
	LONGLONG interval = (currentInterval.QuadPart - beforeInterval.QuadPart);

	//Get DeltaTime
	float dt = (float)interval / (float)frequency.QuadPart;

	//Set BeforeTime
	beforeInterval = currentInterval;

	//Return DeltaTime
	return dt;
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
