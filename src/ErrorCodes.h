#pragma once
#include <string>

namespace PODSL 
{
    enum class ErrorCode
    {
        InternalError = 100,
        NotImplemented = 101,
        ReadingFileError,
        ParsingGraphvizError,
        SavingFileError,
    };

    std::string getErrorDescription(ErrorCode errorCode, const std::string& suffix = std::string());
}