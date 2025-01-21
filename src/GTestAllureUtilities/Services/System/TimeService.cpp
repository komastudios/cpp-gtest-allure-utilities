#include "TimeService.h"

#include <chrono>

namespace systelab { namespace gtest_allure { namespace service {

	TimeService::TimeService()
	{
	}

	int64_t TimeService::getCurrentTime() const
	{
	    auto now = std::chrono::system_clock::now();
	    auto duration = now.time_since_epoch();
	    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	}

}}}
