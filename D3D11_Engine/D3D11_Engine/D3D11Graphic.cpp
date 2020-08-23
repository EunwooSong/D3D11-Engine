#include "stdafx.h"
#include "D3D11Graphic.h"

D3D11Graphic::D3D11Graphic()
{
}

D3D11Graphic::~D3D11Graphic()
{
}

bool D3D11Graphic::Initialize(int, int, bool, HWND, bool, float, float)
{
	return false;
}

void D3D11Graphic::Shutdown()
{
}

void D3D11Graphic::BeginScene(float, float, float, float)
{
}

void D3D11Graphic::EndScene()
{
}

ID3D11Device* D3D11Graphic::GetD3D11Device()
{
	return nullptr;
}

ID3D11DeviceContext* D3D11Graphic::GetDeviceContext()
{
	return nullptr;
}

void D3D11Graphic::GetProjectionMatrix(XMMATRIX&)
{
}

void D3D11Graphic::GetWorldMatrix(XMMATRIX&)
{
}

void D3D11Graphic::GetOrthoMatrix(XMMATRIX&)
{
}

void D3D11Graphic::GetVideoCardInfo(char*, int&)
{
}
