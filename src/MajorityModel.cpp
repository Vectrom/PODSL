#include "MajorityModel.h"
#include "Exception.h"
#include "PODSLEnums.h"

using namespace podsl;

MajorityModel::MajorityModel(uint64_t groupSize) :
    _groupSize(groupSize)
{}

std::map<std::string, int> MajorityModel::calculateOneStep(Graph& graph)
{
    std::set<size_t> group;
    while(group.size() < _groupSize)
        group.insert(graph.getRandomVertexIndex());

    size_t positiveOpinionsCount = 0;
    size_t negativeOpinionsCount = 0;

    for(size_t vertex : group)
    {
        if (graph.getOpinion(vertex) == -1)
            negativeOpinionsCount++;
        else
            positiveOpinionsCount++;
    }
    
    std::map<std::string, int> changes;

    int opinionToSet = positiveOpinionsCount > negativeOpinionsCount ? 1 : -1;
    for (size_t vertex : group)
    {
        if (graph.getOpinion(vertex) == opinionToSet)
            continue;

        graph.setOpinion(vertex, opinionToSet);
        changes[graph.getIndex(vertex)] = opinionToSet;
    }

    return changes;
}

ModelType MajorityModel::getModelType() const
{
    return ModelType::Majority;
}

void MajorityModel::checkMajorityModelRequirements(const Graph& graph) const
{
    if (_groupSize > graph.getNumberOfVertices())
        throw Exception(ErrorCode::TooLargeGroupError);

    if (!graph.isComplete())
        throw Exception(ErrorCode::NotCompleteGraphError, "MajorityModel can be used only for complete graph.");
}