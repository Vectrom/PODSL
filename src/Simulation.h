#pragma once
#include "Graph.h"
#include "ModelBase.h"

class Simulation
{
public:
    Simulation(const ModelBase& model, const Graph& graph);

private:
    const ModelBase& _model;
    Graph _graph;
};