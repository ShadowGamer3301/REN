#pragma once
#include "Framework.h"

#ifdef TARGET_MS_WIN32

namespace REN
{
	//Declare extern class
	class Application;

	enum class EventType : int
	{
		EventType_Null = 0, //Type used as placeholder or where type cannot be defined
		EventType_KeyPress = 1, //When keyboard key was pressed
		EventType_KeyRelease = 2, //When keyboard key was released
		EventType_KeyHold = 3, //When keyboard key is being held,
		EventType_CursorMove = 4, //When mouse cursor was moved
		EventType_CursorLeave = 5, //When mouse cursor left current window
		EventType_CursorEnter = 6, //When mouse cursor entered current window
		EventType_MousePress = 7, //When mouse button was pressed
		EventType_MouseRelease = 8, //When mouse button was released
		EventType_MouseHold = 9, //When mouse button is being held
	};

	struct Event
	{
		EventType type = EventType::EventType_Null;
	};

	struct KeyEvent : public Event
	{
		int key = 0;
		int action = 0;
		int mods = 0;
		int scancode = 0;
	};

	struct CursorEvent : public Event
	{
		double x;
		double y;
	};

	struct MouseEvent : public Event
	{
		int key = 0;
		int action = 0;
		int mods = 0;
	};

	class EventHandler
	{
	public:
		static void SetApplicationPtr(Application* ptr);
		static void PushEvent(Event* ev);
		static void HandleEvents();

	private:
		static EventHandler mMainHandler;
		std::vector<Event*> vecEventBuffer;
		Application* pApp;
	};
}

#endif