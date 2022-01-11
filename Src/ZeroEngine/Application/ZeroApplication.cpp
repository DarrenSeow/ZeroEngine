#include "pch.h"
#include "ZeroApplication.h"



namespace ZeroEngine
{
	ZeroApplication::ZeroApplication() :
		m_running{true},
		m_graphicsEngine{}
	{
	}
	void ZeroApplication::OnInit()
	{
	}
	void ZeroApplication::OnUpdate()
	{
		while (m_running)
		{

			if (!m_graphicsEngine.WindowProcessMessage())
			{
				m_running = false;
			}
			m_graphicsEngine.DrawFrame();
		}
	}
}

