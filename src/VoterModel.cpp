#include "VoterModel.h"

VoterModel::VoterModel(const Graph& graph) :
    ModelBase(graph)
{}

std::map<std::string, int> VoterModel::calculateOneStep()
{
    size_t agentA = _graph.getRandomVertexIndex();
    while(!_graph.hasAdjacentVertices(agentA))
        agentA = _graph.getRandomVertexIndex();

    size_t agentB = _graph.getRandomAdjacentVertexIndex(agentA);
    
    std::map<std::string, int> changes;
    int newOpinion = _graph.getOpinion(agentB);
    _graph.setOpinion(agentA, newOpinion);
    changes[_graph.getIndex(agentA)] = newOpinion;

    return changes;
}
