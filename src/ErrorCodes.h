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
        ParsingPajekError,
        SavingFileError,
        TooLargeGroupError,
        NotCompleteGraphError,
        ExtensionNotSupported,
    };

    std::string getErrorDescription(ErrorCode errorCode, const std::string& suffix = std::string());
}