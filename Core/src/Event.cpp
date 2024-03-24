#include "Event.h"
#include "Application.h"

#ifdef TARGET_MS_WIN32

using namespace REN;
EventHandler EventHandler::mMainHandler;

void EventHandler::SetApplicationPtr(Application* ptr)
{
	mMainHandler.pApp = ptr;
}

void EventHandler::PushEvent(Event* ev)
{
	mMainHandler.vecEventBuffer.push_back(ev);
}

void EventHandler::HandleEvents()
{
	for (auto& ev : mMainHandler.vecEventBuffer)
	{
		mMainHandler.pApp->OnEvent(ev);
		delete ev;
	}

	mMainHandler.vecEventBuffer.clear();
}
#endif

