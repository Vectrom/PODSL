#include "MajorityModel.h"
#include "PODSLEnums.h"

using namespace podsl;

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
