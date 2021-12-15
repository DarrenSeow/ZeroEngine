#include "pch.h"
#include "ZeroApplication.h"



namespace ZeroEngine
{
	ZeroApplication::ZeroApplication() :
		m_running{true},
		m_window{}
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
		}
	}
}

