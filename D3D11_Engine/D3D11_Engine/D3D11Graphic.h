#pragma once
#define FULL_SCREEN false
#define VSYNC_ENABLE true
#define SCREEN_DEPTH 1000.0f
#define SCREEN_NEAR 0.1f

class D3D11Graphic
{
private:
	bool m_vsync_enable = false;
	int m_videoCardMemory = 0;
	char m_videoCardDescription[128] = { 0, };
	IDXGISwapChain* pswapChain = nullptr;
	ID3D11Device* pd3d11_device = nullptr;
	ID3D11DeviceContext* pdeviceContext = nullptr;
	ID3D11RenderTargetView* prenderTargetView = nullptr;
	ID3D11Texture2D* pdepthStencilBuffer = nullptr;
	ID3D11DepthStencilState* pdepthStencilState = nullptr;
	ID3D11DepthStencilView* pdepthStencilView = nullptr;
	ID3D11RasterizerState* prasterState = nullptr;
	XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX orthoMatrix;

public:
	D3D11Graphic();
	~D3D11Graphic();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetD3D11Device();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);
};