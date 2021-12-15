#pragma once

#include <Windows.h>
#include <string>
namespace ZeroEngine
{
	class ZeroWindow
	{
		HINSTANCE m_hInstance;
		HWND m_windowHandle;
		HACCEL m_accelTable;
		HDC m_deviceContext;
		
		std::string m_title;

		unsigned int m_windowWidth;
		unsigned int m_windowHeight;
		unsigned int m_clientWidth;		// Width of client area of window
		unsigned int m_clientHeight;	// Height of client area of window
		bool m_isPaused;
		bool m_isResized;

		static LRESULT CALLBACK OnWinProc(HWND _windowHandle, UINT _message, WPARAM _wParam, LPARAM _lParam);
	public:
		ZeroWindow();
		~ZeroWindow();
		ZeroWindow(const ZeroWindow&) = delete;
		ZeroWindow& operator=(const ZeroWindow&) = delete;
		bool ProcessMessage();
		const unsigned int GetWindowWidth();
		const unsigned int GetWindowHeight();
		const bool GetIsResized();
		void SetIsResized(const bool _isResized);
	};
}