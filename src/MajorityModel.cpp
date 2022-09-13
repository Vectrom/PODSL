#include "MajorityModel.h"
#include "Exception.h"
#include "PODSLEnums.h"

using namespace podsl;

MajorityModel::MajorityModel(uint64_t groupSize) :
    _groupSize(groupSize)
{}

std::map<std::string, int> MajorityModel::calculateOneStep(Graph& graph)
{
    if (_groupSize == 0)
        return {};

    std::set<size_t> group;
    const size_t vertexIndex = graph.getRandomVertexIndex();
    group.insert(vertexIndex);

    const size_t numberOfAdjacentVertices = graph.getNumberOfAdjacentVertices(vertexIndex);
    if (numberOfAdjacentVertices <= _groupSize - 1)
    {
        auto adjacentVertices = graph.getAdjacentVerticesIndexes(vertexIndex);
        group.insert(adjacentVertices.begin(), adjacentVertices.end());
    }
    else
    {
        while (group.size() < _groupSize)
        {
            group.insert(graph.getRandomAdjacentVertexIndex(vertexIndex));
        }
    }

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
}