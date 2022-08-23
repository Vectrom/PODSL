#pragma once
#include <string>

namespace podsl
{
    enum class ModelType
    {
        Custom,
        Majority,
        QVoter,
        Sznajd,
        Voter
    };

    std::string modelTypeToString(ModelType modelType);
    ModelType stringToModelType(const std::string& modelType);
}
