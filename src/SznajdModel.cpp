#include "SznajdModel.h"
#include <windows.h>

SznajdModel::SznajdModel(const Graph& graph) :
    ModelBase(graph)
{}

void SznajdModel::calculateOneStep()
{
    size_t agentA = _graph.getRandomVertexIndex();
    while (!_graph.hasAdjacentVertices(agentA))
        agentA = _graph.getRandomVertexIndex();

    size_t agentB = _graph.getRandomAdjacentVertexIndex(agentA);

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
        }

    }
    std::string a = std::string("Agent A") + std::to_string(agentA) + " agent B" + std::to_string(agentB);
    OutputDebugString(a.c_str());
}
