#pragma once


#include "..\Windows\ZeroWindow.h"
#include "..\Graphics\GraphicsEngine.h"
namespace ZeroEngine
{
	class ZeroApplication
	{
		bool m_running;
		ZeroWindow m_window;
		GraphicsEngine m_graphicsEngine;
	public:

		ZeroApplication(const std::string& _applicationName, const unsigned int _width, const unsigned int _height);
		void OnInit();
		void OnUpdate();
	};
}