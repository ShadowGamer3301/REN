#pragma once
#include "Framework.h"
#include "Exception.h"
#include "Event.h"

#ifdef TARGET_MS_WIN32

namespace REN
{
	static void WndKeyCallback(GLFWwindow* pWnd, int key, int scancode, int action, int mods);
	static void WndCharCallback(GLFWwindow* pWnd, unsigned int codepoint);
	static void WndMousePosCallback(GLFWwindow* pWnd, double xpos, double ypos);
	static void WndCursorEnterCallback(GLFWwindow* pWnd, int entered);
	static void WndMouseBtnCallback(GLFWwindow* pWnd, int button, int action, int mods);

	class Window
	{
		friend class Graphics;
	public:
		Window(int width, int height, const char* name, bool fullscreen);
		~Window();

		void Show();
		void Hide();

		bool UpdateWindow();

	private:
		GLFWwindow* pWnd;
		bool fs;
	};
}

#endif