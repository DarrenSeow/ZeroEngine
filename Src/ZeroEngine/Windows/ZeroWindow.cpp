#include "pch.h"
#include "ZeroWindow.h"


namespace ZeroEngine
{
	ZeroWindow::ZeroWindow(const std::string& _windowName, const unsigned int _width, const unsigned int _height) :
		m_hInstance{GetModuleHandle(NULL)},
		m_windowHandle{NULL},
		m_accelTable{NULL},
		m_deviceContext{NULL},
		m_title{ _windowName },
		m_windowWidth{ _width },
		m_windowHeight{ _height },
		m_clientWidth{0},
		m_clientHeight{0},
		m_isPaused{false},
		m_isResized{false}
	{
		// Get current application instance handle
		

		// Window with same identity exist, unable to register another window under same identity
		WNDCLASSA winClass;
		if (GetClassInfo(m_hInstance, m_title.c_str(), (LPWNDCLASSA)&winClass))
		{
			MessageBox(NULL, "Window already exist!", "Error", MB_ICONEXCLAMATION);
			return;
		}

		// Register a new window instance with suitable settings
		winClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		winClass.hInstance = m_hInstance;
		winClass.lpfnWndProc = ZeroWindow::OnWinProc;
		winClass.cbClsExtra = 0;
		winClass.cbWndExtra = sizeof(LONG_PTR);;
		winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		winClass.lpszMenuName = nullptr;
		winClass.lpszClassName = m_title.c_str();

		

		if (!RegisterClass(&winClass))
		{
			MessageBox(NULL, "Failed to register window!", "Error", MB_ICONEXCLAMATION);
			return;
		}

		// Create window using registered settings
		DWORD dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE | WS_OVERLAPPEDWINDOW;
		m_windowHandle = CreateWindow
		(
			m_title.c_str(),					// Name of Class
			m_title.c_str(),					// Title of window
			dwStyle,							// Style of window
			CW_USEDEFAULT,						// Starting x position of window
			CW_USEDEFAULT,						// Starting y position of window
			m_windowWidth,						// Width of window, including borders
			m_windowHeight,						// Height of window, including borders and captions
			GetDesktopWindow(),					// Parent window
			nullptr,							// Menu for window
			m_hInstance,						// Main Win32 handle instance
			this								// lParam for the WM_CREATE message of this window
		);

		if (!m_windowHandle)
		{
			throw std::exception( "Failed to Create Window" );
			//MessageBox(NULL, "Failed to create window!", "Error", MB_ICONEXCLAMATION);
			
		}
		SetWindowText(m_windowHandle, m_title.c_str());
		// Update client data of created window
		RECT rect;
		GetClientRect(m_windowHandle, &rect);
		m_clientWidth = rect.right - rect.left;
		m_clientHeight = rect.bottom - rect.top;
		UpdateWindow(
			m_windowHandle
		);
	}

	ZeroWindow::~ZeroWindow()
	{
		UnregisterClass(m_title.c_str(), m_hInstance);
	}

	bool ZeroWindow::ProcessMessage()
	{
		// Get messages sent to current window and process them
		
		MSG message;
		while (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{					
				return false;
			}
			// Window currently inactive, stop processing messages
			if (m_isPaused)
				continue;

			// Process Accelerator Table Keys
			if (!TranslateAccelerator(m_windowHandle, m_accelTable, &message))
			{
				//GetMessage(&message, NULL, 0, 0);
				TranslateMessage(&message);
				DispatchMessage(&message);
					
			}
		}
		return true;
	}

	const unsigned int ZeroWindow::GetWindowWidth() const
	{
		return m_windowWidth;
	}

	const unsigned int ZeroWindow::GetWindowHeight() const
	{
		return m_windowHeight;
	}

	const bool ZeroWindow::GetIsResized()
	{
		return m_isResized;
	}

	void ZeroWindow::SetIsResized(const bool _isResized)
	{
		m_isResized = _isResized;
	}

	const HWND ZeroWindow::GetWindowHandle()
	{
		return m_windowHandle;
	}

	const HINSTANCE ZeroWindow::GetInstance() const
	{
		return m_hInstance;
	}

	const HWND ZeroWindow::GetHWND() const
	{
		return m_windowHandle;
	}


	LRESULT CALLBACK ZeroWindow::OnWinProc(HWND _windowHandle, UINT _message, WPARAM _wParam, LPARAM _lParam)
	{
		//window creation event
		if (_message == WM_NCCREATE)
		{
			LPCREATESTRUCT pcs = (LPCREATESTRUCT)_lParam;
			ZeroWindow* zeroWindow = (ZeroWindow*)pcs->lpCreateParams;
			zeroWindow->m_windowHandle = _windowHandle;
			SetWindowLongPtr(
				_windowHandle,
				GWLP_USERDATA,
				reinterpret_cast<LONG_PTR>(zeroWindow));
			return 1;
		}

		ZeroWindow* zeroWindow = nullptr;
		zeroWindow = (ZeroWindow*)GetWindowLongPtr(_windowHandle, GWLP_USERDATA);

		if (zeroWindow)
		{
			switch (_message)
			{
			case WM_SIZE:
				zeroWindow->m_isResized = true;
				break;
			case WM_CLOSE:
				DestroyWindow(_windowHandle);
				break;
			case WM_DESTROY:				
				PostQuitMessage(0);
				break;
			default:
				break;
			}

		}
		return DefWindowProc(_windowHandle, _message, _wParam, _lParam);
	}

}
