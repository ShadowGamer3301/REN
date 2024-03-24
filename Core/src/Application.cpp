#include "Application.h"

#ifdef TARGET_MS_WIN32

using namespace REN;

Application::Application()
{
	//Create application window
	pWnd = new Window(800, 600, "REN (WIN32 | D3D11)", false);
	
	//Check if window was created properly
	if (pWnd == nullptr)
		throw Exception();

	pGfx = new Graphics(pWnd);
	if (pGfx == nullptr)
		throw Exception();
}

Application::~Application()
{
	delete pGfx;
	delete pWnd;
}

#endif

