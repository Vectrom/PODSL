#include "VoterModel.h"
#include "PODSLEnums.h"

using namespace podsl;

std::map<std::string, int> VoterModel::calculateOneStep(Graph& graph)
{
    size_t agentA = graph.getRandomVertexIndex();
    while(!graph.hasAdjacentVertices(agentA))
        agentA = graph.getRandomVertexIndex();

    size_t agentB = graph.getRandomAdjacentVertexIndex(agentA);
    
    std::map<std::string, int> changes;
    int newOpinion = graph.getOpinion(agentB);
    graph.setOpinion(agentA, newOpinion);
    changes[graph.getIndex(agentA)] = newOpinion;

    return changes;
}

ModelType VoterModel::getModelType() const
{
    return ModelType::Voter;
}
