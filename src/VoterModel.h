#pragma once
#include "Graph.h"
#include "ModelBase.h"

class VoterModel : public ModelBase
{
public:
    VoterModel(const Graph& graph);
    virtual std::map<std::string, int> calculateOneStep();

};