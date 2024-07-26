#pragma once

#include <d3d11.h>

enum ImFont_ : int
{
	ImFont_Main
};

class CGui
{
public:
	CGui();
	~CGui();

	bool Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
	void Shutdown();
	void Render(const char* title, POINTS size, bool* b_open = 0);

	bool IsGuiMoving();
	bool MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	ID3D11Device* GetDevice() { return m_pDevice; };
	ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; };
	HWND GetWindow() { return m_hWnd; };

private:
	HWND m_hWnd;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
};
