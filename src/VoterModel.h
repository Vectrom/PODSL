#pragma once
#include "Graph.h"
#include "ModelBase.h"

class VoterModel : public ModelBase
{
public:
    VoterModel(const Graph& graph);
    virtual void calculateOneStep();

};