#pragma once
#include "Graph.h"

class ModelBase
{
    public:
        ModelBase(const Graph& graph);
        virtual std::map<std::string, int> calculateOneStep() = 0;
        const Graph& getGraph() const { return _graph; };

    protected:
        Graph _graph;

};