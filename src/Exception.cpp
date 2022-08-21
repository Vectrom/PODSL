#include "Exception.h"
#include <sstream>

using namespace podsl;

static constexpr const char* ErrorCodePrefix = "ERROR(";
static constexpr const char* ErrorCodeSuffix = ")";

Exception::Exception(ErrorCode errorCode, const std::string& errorMessage) :
    std::exception(),
    _errorCode(errorCode),
    _errorMessage(createErrorMessage(errorCode, errorMessage))
{
}

const char* Exception::what() const noexcept
{
    return _errorMessage.c_str();
}

std::string Exception::createErrorMessage(ErrorCode errorCode, const std::string& errorMessage)
{
    std::ostringstream stream;
    stream << ErrorCodePrefix << static_cast<int>(errorCode) << ErrorCodeSuffix
        << ": " << getErrorDescription(errorCode, errorMessage);

    return stream.str();
}
