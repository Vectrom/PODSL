#pragma once
#include "ErrorCodes.h"
#include <exception>

namespace podsl
{
    class Exception : public std::exception
    {
    public:
        Exception(ErrorCode errorCode, const std::string& errorMessage = {});
        
        virtual const char* what() const noexcept override;
    private:
        std::string _errorMessage;

        static std::string createErrorMessage(ErrorCode errorCode, const std::string& errorMessage);
    };
}