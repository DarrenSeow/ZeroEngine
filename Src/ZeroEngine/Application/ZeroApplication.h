#pragma once


#include "../Windows/ZeroWindow.h"

namespace ZeroEngine
{
	class ZeroApplication
	{
		bool m_running;
		ZeroWindow m_window;
	public:

		ZeroApplication();
		void OnInit();
		void OnUpdate();
	};
}