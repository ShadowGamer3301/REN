#include "Editor.h"

#ifdef TARGET_MS_WIN32

int main(void) try
{
	auto app = REN::CreateNewApplication();
	REN::EventHandler::SetApplicationPtr(app);
	app->Run();
	delete app;
	return 0;
}
catch (REN::Exception& e)
{
	printf("%s", e.what());
	return 1;
}

#endif