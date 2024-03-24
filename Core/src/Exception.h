#pragma once
#include "Framework.h"

#ifdef TARGET_MS_WIN32

namespace REN
{
	class Exception : public std::exception
	{
	public:
		Exception(std::source_location loc = std::source_location::current());
		const char* what() const noexcept override;

	protected:
		int line;
		std::string func, file;
		mutable std::string wBuffer;
	};
}

#endif