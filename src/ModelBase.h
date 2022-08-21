#pragma once
#include "Graph.h"

namespace PODSL
{
    enum class ModelType;

    class ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph) = 0;
        virtual ModelType getModelType() const;
        virtual ~ModelBase() = default;
    };
}