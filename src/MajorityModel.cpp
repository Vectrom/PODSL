#include "MajorityModel.h"
#include "PODSLEnums.h"

std::map<std::string, int> MajorityModel::calculateOneStep(Graph& graph)
{
    (void)graph;
    std::map<std::string, int> changes;
    return changes;
}

ModelType MajorityModel::getModelType() const
{
    return ModelType::Majority;
}
