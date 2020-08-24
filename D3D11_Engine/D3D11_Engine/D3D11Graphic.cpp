#include "stdafx.h"
#include "D3D11Graphic.h"

D3D11Graphic::D3D11Graphic()
{
}

D3D11Graphic::~D3D11Graphic()
{
}

bool D3D11Graphic::Initialize(int screenWidth, int screenHeight, bool useVsync, HWND hWnd, bool fullscreen, float screenDepth, float screenNear)
{
	m_vsync_enable = useVsync;

	//------------------------------------------------------------------------
	// Get Graphic Card Info, Check Display Mode, Ready Vsync
	//------------------------------------------------------------------------
	IDXGIFactory* factory = nullptr;

	if (FAILED(CreateDXGIFactory(_uuidof(IDXGIFactory), (void**)&factory)))
		return false;

	IDXGIAdapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
		return false;

	IDXGIOutput* adapterOutput = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
		return false;

	unsigned int numModes = 0;
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
		return false;

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
		return false;

	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
		return false;

	unsigned int numerator = 0;
	unsigned int denominator = 0;
	for (unsigned int i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == (unsigned int)screenWidth) {
			if (displayModeList[i].Height == (unsigned int)screenHeight) {
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	if (FAILED(adapter->GetDesc(&adapterDesc)))
		return false;

	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	if (wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0)
		return false;

	SAFE_DELETE_ARRAY(displayModeList);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);

	//------------------------------------------------------------------------
	// Initialize D3D11
	//------------------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;

	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (m_vsync_enable) {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Window or FullScreen
	if (fullscreen) {
		swapChainDesc.Windowed = false;
	}
	else {
		swapChainDesc.Windowed = true;
	}

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&pswapChain,
		&pd3d11_device,
		NULL,
		&pdeviceContext)))
		return false;

	ID3D11Texture2D* backBufferPtr = nullptr;
	if(FAILED(pswapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr)))
		return false;

	if (FAILED(pd3d11_device->CreateRenderTargetView(backBufferPtr, NULL, &prenderTargetView)))
		return false;

	SAFE_RELEASE(backBufferPtr);

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	if (FAILED(pd3d11_device->CreateTexture2D(&depthBufferDesc, NULL, &pdepthStencilBuffer)))
		return false;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	if (FAILED(pd3d11_device->CreateDepthStencilState(&depthStencilDesc, &pdepthStencilState)))
		return false;
	pdeviceContext->OMSetDepthStencilState(pdepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(pd3d11_device->CreateDepthStencilView(pdepthStencilBuffer, &depthStencilViewDesc, &pdepthStencilView)))
		return false;

	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(pd3d11_device->CreateRasterizerState(&rasterDesc, &prasterState)))
		return false;

	pdeviceContext->RSSetState(prasterState);

	D3D11_VIEWPORT viewport;
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	pdeviceContext->RSSetViewports(1, &viewport);

	float fieldOfView = XM_PI / 4.0f;
	float screenAspect = (float)screenWidth / (float)screenHeight;

	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
	m_worldMatrix = XMMatrixIdentity();
	m_orthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	return true;
}

void D3D11Graphic::Dispose()
{
	if (pswapChain)
		pswapChain->SetFullscreenState(false, NULL);

	if (prasterState)
		SAFE_RELEASE(prasterState);
	if (pdepthStencilView)
		SAFE_RELEASE(pdepthStencilView);
	if (pdepthStencilState)
		SAFE_RELEASE(pdepthStencilState);
	if (pdepthStencilBuffer)
		SAFE_RELEASE(pdepthStencilBuffer);
	if (prenderTargetView)
		SAFE_RELEASE(prenderTargetView);
	if (pdeviceContext)
		SAFE_RELEASE(pdeviceContext);
	if (pd3d11_device)
		SAFE_RELEASE(pd3d11_device);
	if (pswapChain)
		SAFE_RELEASE(pswapChain);
}

void D3D11Graphic::BeginScene(Color color)
{
	pdeviceContext->ClearRenderTargetView(prenderTargetView, color.getColor_RGBA());
	pdeviceContext->ClearDepthStencilView(pdepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3D11Graphic::EndScene()
{
	if (m_vsync_enable)
		pswapChain->Present(1, 0);
	else
		pswapChain->Present(0, 0);
}

ID3D11Device* D3D11Graphic::GetD3D11Device()
{
	return pd3d11_device;
}

ID3D11DeviceContext* D3D11Graphic::GetDeviceContext()
{
	return pdeviceContext;
}

void D3D11Graphic::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
}

void D3D11Graphic::GetWorldMatrix(XMMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;
}

void D3D11Graphic::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
}

void D3D11Graphic::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
}
