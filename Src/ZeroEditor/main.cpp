
#include <pch.h>

#include <ZeroApplication.h>
#include <memory>


int main()
{
	try
	{
		ZeroEngine::ZeroApplication application{ "Zero Editor",1280,720 };
		application.OnInit();
		application.OnUpdate();	
	}
	catch (const std::exception& e)
	{
        int msgboxID = MessageBox(
            NULL,
            e.what(),
            "Error Message",
            MB_ICONERROR | MB_OK | MB_DEFBUTTON2
        );
	}
}