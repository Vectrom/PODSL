#include "QVoterModel.h"
#include "PODSLEnums.h"

using namespace podsl;

podsl::QVoterModel::QVoterModel(uint64_t q/*, double probability*/) :
    _q(q)/*,
    _probability(probability)*/
{
}

std::map<std::string, int> QVoterModel::calculateOneStep(Graph& graph)
{
    const size_t vertexIndex = graph.getRandomVertexIndex();

    const size_t numberOfAdjacentVertices = graph.getNumberOfAdjacentVertices(vertexIndex);
    std::set<size_t> randomNeighbors;

    if (numberOfAdjacentVertices <= _q - 1)
    {
        auto adjacentVertices = graph.getAdjacentVerticesIndexes(vertexIndex);
        randomNeighbors.insert(adjacentVertices.begin(), adjacentVertices.end());
    }
    else
    {
        while (randomNeighbors.size() < _q)
        {
            randomNeighbors.insert(graph.getRandomAdjacentVertexIndex(vertexIndex));
        }
    }

    std::map<std::string, int> changes;
    int firstNeighborOpinion = graph.getOpinion(*randomNeighbors.begin());
    if (std::all_of(randomNeighbors.begin(),
        randomNeighbors.end(),
        [&graph, &firstNeighborOpinion] (size_t vertex) { return graph.getOpinion(vertex) == firstNeighborOpinion; }))
    {
        graph.setOpinion(vertexIndex, firstNeighborOpinion);
        changes[graph.getIndex(vertexIndex)] = firstNeighborOpinion;
    }

    return changes;
}

ModelType QVoterModel::getModelType() const
{
    return ModelType::QVoter;
}
