#include "PODSLEnums.h"

using namespace podsl;

std::string podsl::modelTypeToString(ModelType modelType)
{
    switch(modelType)
    {
    case ModelType::Custom:
        return "CustomModel";
    case ModelType::Majority:
        return "MajorityModel";
    case ModelType::QVoter:
        return "QVoterModel";
    case ModelType::Sznajd:
        return "SznajdModel";
    case ModelType::Voter:
        return "VoterModel";
    }

    return "CustomModel"; // to avoid compiler warning
}

ModelType podsl::stringToModelType(const std::string& modelType)
{
    if (modelType == "CustomModel")
        return ModelType::Custom;
    else if (modelType == "MajorityModel")
        return ModelType::Majority;
    else if (modelType == "QVoterModel")
        return ModelType::QVoter;
    else if (modelType == "SznajdModel")
        return ModelType::Sznajd;
    else if (modelType == "VoterModel")
        return ModelType::Voter;

    return ModelType::Custom; // to avoid compiler warning
}