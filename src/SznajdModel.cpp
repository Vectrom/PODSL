#include "SznajdModel.h"
#include "PODSLEnums.h"

using namespace PODSL;

std::map<std::string, int> SznajdModel::calculateOneStep(Graph& graph)
{
    size_t agentA = graph.getRandomVertexIndex();
    while (!graph.hasAdjacentVertices(agentA))
        agentA = graph.getRandomVertexIndex();

    size_t agentB = graph.getRandomAdjacentVertexIndex(agentA);

    std::map<std::string, int> changes;

    if(graph.getOpinion(agentA) == graph.getOpinion(agentB))
    {
        std::set<size_t> neighborsOfAgentA = graph.getAdjacentVerticesIndexes(agentA);
        neighborsOfAgentA.erase(agentB);
        std::set<size_t> neighborsOfAgentB = graph.getAdjacentVerticesIndexes(agentB);
        neighborsOfAgentB.erase(agentA);
        neighborsOfAgentA.merge(neighborsOfAgentB);

        for(const size_t neighbor : neighborsOfAgentA)
        {
            const int opinion = graph.getOpinion(neighbor);
            graph.setOpinion(neighbor, -opinion);
            changes[graph.getIndex(neighbor)] = -opinion;
        }
    }
    return changes;
}

ModelType SznajdModel::getModelType() const
{
    return ModelType::Sznajd;
}
