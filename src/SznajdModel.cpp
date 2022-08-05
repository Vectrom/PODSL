#include "SznajdModel.h"

SznajdModel::SznajdModel(const Graph& graph) :
    ModelBase(graph)
{}

std::map<std::string, int> SznajdModel::calculateOneStep()
{
    size_t agentA = _graph.getRandomVertexIndex();
    while (!_graph.hasAdjacentVertices(agentA))
        agentA = _graph.getRandomVertexIndex();

    size_t agentB = _graph.getRandomAdjacentVertexIndex(agentA);

    std::map<std::string, int> changes;

    if(_graph.getOpinion(agentA) == _graph.getOpinion(agentB))
    {
        std::set<size_t> neighborsOfAgentA = _graph.getAdjacentVerticesIndexes(agentA);
        neighborsOfAgentA.erase(agentB);
        std::set<size_t> neighborsOfAgentB = _graph.getAdjacentVerticesIndexes(agentB);
        neighborsOfAgentB.erase(agentA);
        neighborsOfAgentA.merge(neighborsOfAgentB);

        for(const size_t neighbor : neighborsOfAgentA)
        {
            const int opinion = _graph.getOpinion(neighbor);
            _graph.setOpinion(neighbor, -opinion);
            changes[_graph.getIndex(neighbor)] = -opinion;
        }
    }
    return changes;
}
