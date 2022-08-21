#include "QVoterModel.h"
#include "PODSLEnums.h"

using namespace PODSL;

std::map<std::string, int> QVoterModel::calculateOneStep(Graph& graph)
{
    (void)graph;
    std::map<std::string, int> changes;
    return changes;
}

ModelType QVoterModel::getModelType() const
{
    return ModelType::QVoter;
}
