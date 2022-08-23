#pragma once
#include <string>

namespace podsl 
{
    enum class ErrorCode
    {
        InternalError = 100,
        NotImplemented = 101,
        ReadingFileError,
        ParsingGraphvizError,
        SavingFileError,
        TooLargeGroupError,
        NotCompleteGraphError
    };

    std::string getErrorDescription(ErrorCode errorCode, const std::string& suffix = std::string());
}