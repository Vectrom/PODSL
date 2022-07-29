#include "VoterModel.h"

VoterModel::VoterModel(const Graph& graph) :
    ModelBase(graph)
{}

void VoterModel::calculateOneStep()
{
    size_t agentA = _graph.getRandomVertexIndex();
    while(!_graph.hasAdjacentVertices(agentA))
        agentA = _graph.getRandomVertexIndex();

    size_t agentB = _graph.getRandomAdjacentVertexIndex(agentA);
    
    _graph.setOpinion(agentA, _graph.getOpinion(agentB));
}
