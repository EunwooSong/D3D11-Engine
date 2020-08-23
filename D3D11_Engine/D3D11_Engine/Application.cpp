#include "stdafx.h"
#include "Application.h"
#include "D3D11Graphic.h"

Application::Application()
{
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&frequency);

	d3d11Graphic = new D3D11Graphic();

}

Application::~Application()
{
}

void Application::Update(float dt)
{
}

void Application::Render()
{
}

Application* Application::Instance()
{
	return nullptr;
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


	return HWND();
}

void Application::InitWindow(HINSTANCE hInstance)
{
}

void Application::InitD3D11(HWND hWnd)
{

}

void Application::InitDeltaTime()
{
}

void Application::ReleseD3D11()
{
}

void Application::DeleteManager()
{
}

int Application::DoMainLoop(Scene* firstScene)
{
	return 0;
}

float Application::getDeltaTime()
{
	return 0.0f;
}

HWND Application::GetHwnd() const
{
	return HWND();
}

ID3D11Device* Application::GetD3D11Device() const
{
	return nullptr;
}

ID3D11DeviceContext* Application::GetD3D11DeviceContext() const
{
	return nullptr;
}
