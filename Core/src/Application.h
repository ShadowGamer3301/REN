#pragma once
#include "Framework.h"
#include "Window.h"
#include "Event.h"
#include "Graphics.h"

#ifdef TARGET_MS_WIN32
	
namespace REN
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		//Prevent class from being coppied or assigned
		Application(const Application&) = delete;
		Application operator=(const Application&) = delete;

		virtual int Run() = 0; //Needs to be overriden by child class
		virtual int OnEvent(Event* ev) = 0; //Needs to be overriden by child class

	protected:
		Window* pWnd;
		Graphics* pGfx;
	};

	//Needs to be defined in client (should return ptr to child class)
	Application* CreateNewApplication();
}

#endif