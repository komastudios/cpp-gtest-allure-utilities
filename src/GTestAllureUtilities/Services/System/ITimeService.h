#pragma once

#include <string>
#include <cstdint>

namespace systelab { namespace gtest_allure { namespace service {

	class ITimeService
	{
	public:
		virtual ~ITimeService() = default;

		virtual int64_t getCurrentTime() const = 0;
	};

}}}
