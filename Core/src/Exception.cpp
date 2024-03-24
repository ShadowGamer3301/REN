#include "Exception.h"

#ifdef TARGET_MS_WIN32

using namespace REN;

Exception::Exception(std::source_location loc) //Gather basic info about exception
	: file(loc.file_name()), line(loc.line()), func(loc.function_name())
{}

const char* Exception::what() const noexcept
{
	//Return general info about exception (where it happened)

	std::ostringstream oss;
	oss << "Exception caught!\n"
		<< "File: " << file << "\n"
		<< "Func: " << func << "\n"
		<< "Line: " << line << "\n";

	wBuffer = oss.str();

	return wBuffer.c_str();
}

#endif