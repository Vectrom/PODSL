#pragma once
#include "Graph.h"
#include "ModelBase.h"

namespace podsl
{
    class SznajdModel : public ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph);
        virtual ModelType getModelType() const;
    };
}