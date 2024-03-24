#include "Editor.h"

#ifdef TARGET_MS_WIN32

Editor::Editor()
{
	pWnd->Show();
}

Editor::~Editor()
{
	
}

int Editor::Run()
{
	while (pWnd->UpdateWindow())
	{
		REN::EventHandler::HandleEvents();
		pGfx->StartDraw();
		pGfx->EndDraw();
	}

	return 0;
}

int Editor::OnEvent(REN::Event* ev)
{
	switch (ev->type)
	{
	case REN::EventType::EventType_KeyPress:
		printf("Key pressed \n"); break;

	case REN::EventType::EventType_KeyHold:
		printf("Key held \n"); break;

	case REN::EventType::EventType_KeyRelease:
		printf("Key released \n"); break;
	}

	return 0;
}

REN::Application* REN::CreateNewApplication()
{
	return new Editor();
}

#endif