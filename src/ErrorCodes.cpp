#include "ErrorCodes.h"

using namespace podsl;

std::string podsl::getErrorDescription(ErrorCode errorCode, const std::string& suffix)
{
    std::string description;
    switch(errorCode)
    {
    case ErrorCode::InternalError:
        description = "Internal error";
        break;
    case ErrorCode::NotImplemented:
        description = "Not implemented";
        break;
    case ErrorCode::ReadingFileError:
        description = "Reading file error";
        break;
    case ErrorCode::ParsingGraphvizError:
        description = "Parsing Graphviz error";
        break;
    case ErrorCode::SavingFileError:
        description = "Saving file error";
        break;
    }

    if(!description.empty())
    {
        description.append(". ").append(suffix);
    }

    return description;
}
