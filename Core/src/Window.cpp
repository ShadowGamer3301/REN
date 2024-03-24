#include "Window.h"

#ifdef TARGET_MS_WIN32

using namespace REN;

Window::Window(int width, int height, const char* name, bool fullscreen)
	: fs(fullscreen)
{
	//Try to initalize GLFW library
	if (!glfwInit())
		throw Exception();

	//Disable dynamic resizing of window
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Disable default OpenGL API (will be overriden by D3D12)
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	if (fullscreen) //If fullscreen mode is requested fill the primary monitor
		pWnd = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), nullptr);
	else
		pWnd = glfwCreateWindow(width, height, name, nullptr, nullptr);

	//Check if window was created properly
	if (pWnd == nullptr)
		throw Exception();

	//Set all necessary callbacks
	glfwSetCharCallback(pWnd, WndCharCallback);
	glfwSetKeyCallback(pWnd, WndKeyCallback);
	glfwSetMouseButtonCallback(pWnd, WndMouseBtnCallback);
	glfwSetCursorEnterCallback(pWnd, WndCursorEnterCallback);
	glfwSetCursorPosCallback(pWnd, WndMousePosCallback);
}

Window::~Window()
{
	//Free unnecessary memory and shutdown GLFW to avoid memory leaks
	glfwDestroyWindow(pWnd);
	glfwTerminate();
}

void Window::Show()
{
	glfwShowWindow(pWnd);
}

void Window::Hide()
{
	glfwHideWindow(pWnd);
}

bool Window::UpdateWindow()
{
	//Check if any input was passed to window
	glfwPollEvents();

	//Since glfwWindowShouldClose return if window should close
	//negate it for easier use
	return !glfwWindowShouldClose(pWnd);
}


#endif

void REN::WndKeyCallback(GLFWwindow* pWnd, int key, int scancode, int action, int mods)
{
	KeyEvent* pEvent = new KeyEvent();
	
	if (action == GLFW_PRESS)
		pEvent->type = EventType::EventType_KeyPress;
	if (action == GLFW_RELEASE)
		pEvent->type = EventType::EventType_KeyRelease;
	if (action == GLFW_REPEAT)
		pEvent->type = EventType::EventType_KeyHold;

	pEvent->mods = mods;
	pEvent->scancode = scancode;
	pEvent->key = key;
	pEvent->action = action;

	EventHandler::PushEvent(pEvent);
}

void REN::WndCharCallback(GLFWwindow* pWnd, unsigned int codepoint)
{
}

void REN::WndMousePosCallback(GLFWwindow* pWnd, double xpos, double ypos)
{
}

void REN::WndCursorEnterCallback(GLFWwindow* pWnd, int entered)
{
}

void REN::WndMouseBtnCallback(GLFWwindow* pWnd, int button, int action, int mods)
{
}
