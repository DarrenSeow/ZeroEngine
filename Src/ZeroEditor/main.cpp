
#include <pch.h>

#include <ZeroApplication.h>
#include <memory>
int main()
{
	try
	{
		ZeroEngine::ZeroApplication application;
		application.OnInit();
		application.OnUpdate();	
	}
	catch (const std::exception& )
	{
		
	}
}