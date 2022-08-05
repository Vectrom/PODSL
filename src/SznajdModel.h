#pragma once
#include "Graph.h"
#include "ModelBase.h"

class SznajdModel : public ModelBase
{
public:
    SznajdModel(const Graph& graph);
    virtual std::map<std::string, int> calculateOneStep();

};