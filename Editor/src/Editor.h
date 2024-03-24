#pragma once
#include "REN.hpp"

#ifdef TARGET_MS_WIN32

class Editor : public REN::Application
{
public:
	Editor();
	~Editor();

	int Run() override;
	int OnEvent(REN::Event* ev) override;
};

#endif