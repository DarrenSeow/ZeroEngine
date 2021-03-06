#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <Windows.h>
#include <string>
#include <vulkan\vulkan.hpp>
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
		ZeroWindow(const std::string& _windowName, const unsigned int _width,const unsigned int _height);
		~ZeroWindow();
		ZeroWindow(const ZeroWindow&) = delete;
		ZeroWindow& operator=(const ZeroWindow&) = delete;
		bool ProcessMessage();
		const unsigned int GetWindowWidth() const;
		const unsigned int GetWindowHeight() const;
		const bool GetIsResized();
		void SetIsResized(const bool _isResized);
		const HWND GetWindowHandle();

		const HINSTANCE GetInstance() const;
		const HWND GetHWND() const;
		
	};
}