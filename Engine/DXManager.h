#pragma once


#include <dxgi.h>
#include "DataType.h"
#include "ErrorBox.h"
#include <crtdbg.h>


using namespace utility;


class DXManager {
public:
	DXManager();
	DXManager(const DXManager&);
	~DXManager();

	void * operator new(size_t nSize, size_t nAlignment);
	void operator delete(void *pObject, size_t nAlignment);

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void BeginScene(float, float, float, float);
	void EndScene();
	void Shutdown();

	ID3D11Device* GetDevice() { return mPd3dDevice; }
	IDXGISwapChain* GetSwapChain() { return mPSwapChain; }
	ID3D11DeviceContext* GetDeviceContext() { return mPd3dDeviceContext; }
	ID3D11RenderTargetView* GetRenderTargetView(){ return mPRenderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView(){ return mPDepthStencilView; }
	ID3D11Texture2D* GetDepthStencil(){ return pDepthStencil; }
	ID3D11DepthStencilState* GetDepthStencilState(){ return m_depthStencilState; }
	ID3D11BlendState* GetAlphaEnableBlendingState(){ return m_alphaEnableBlendingState; }
	ID3D11BlendState* GetAlphaDisableBlendingState(){ return m_alphaDisableBlendingState; }

	void GetVideoCardInfo(char*, int&);
	Transformations* GetTransf() { return &transf; }
	DirectX::XMMATRIX GetOrthoMatrix(){return m_orthoMatrix;}
	void TurnZBufferOn();
	void TurnZBufferOff();
	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();
	void SetBackBufferRenderTarget();
	void ResetViewport();


public:
	HRESULT initializeDevice(bool);
	HRESULT setupMatrix();
	HRESULT getVideoCardInfo();
	HRESULT initializeRenderTarget();
	HRESULT initializeDepthBufferDesc();
	HRESULT initializeDepthStencilDesc();
	HRESULT initializeAlphaBlendStateDesc();
	HRESULT initializeRasterState();

private:
	ID3D11Device* mPd3dDevice;
	IDXGISwapChain* mPSwapChain;
	ID3D11DeviceContext* mPd3dDeviceContext;
	ID3D11RenderTargetView* mPRenderTargetView;
	ID3D11DepthStencilView* mPDepthStencilView;
	ID3D11Texture2D* pDepthStencil;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilState* m_depthDisabledStencilState;
	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;
	ID3D11RasterizerState* m_rasterState;
	
	D3D11_VIEWPORT vp;
	HWND mHWnd;
	D3D_DRIVER_TYPE mDriverType;
	bool m_vsync_enabled;
	int m_ScreenWidth, m_ScreenHeight, mMuntisampleCount, mNumerator, mDenominator, m_videoCardMemory;
	float m_ScreenNear, m_ScreenDepth;
	Transformations transf;
	DirectX::XMMATRIX m_orthoMatrix;
	char m_videoCardDescription[128];
};