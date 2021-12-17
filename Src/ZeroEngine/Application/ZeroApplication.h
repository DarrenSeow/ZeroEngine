#pragma once


#include "..\Windows\ZeroWindow.h"
#include "..\Graphics\GraphicsEngine.h"
namespace ZeroEngine
{
	class ZeroApplication
	{
		bool m_running;
		
		GraphicsEngine m_graphicsEngine;
	public:

		ZeroApplication();
		void OnInit();
		void OnUpdate();
	};
}