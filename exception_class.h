#pragma once

// �쳣��

#include <string>

class illegalParameterValue
{
public:
	illegalParameterValue(const char* errMsg = "illegal") : errorMessage(errMsg) {}
private:
	std::string errorMessage;
};