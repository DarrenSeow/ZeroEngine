#include "pch.h"
#include "ZeroApplication.h"



namespace ZeroEngine
{
	ZeroApplication::ZeroApplication(const std::string& _applicationName, 
		const unsigned int _width, 
		const unsigned int _height) :
		m_running{true},
		m_window{_applicationName,_width,_height },
		m_graphicsEngine{m_window}
	{
	}
	void ZeroApplication::OnInit()
	{
	}
	void ZeroApplication::OnUpdate()
	{
		while (m_running)
		{

			if (!m_window.ProcessMessage())
			{
				m_running = false;
			}
			m_graphicsEngine.DrawFrame(m_window);
		}
		//vkDeviceWaitIdle(m_graphicsEngine.GetDevice());
	}
}

