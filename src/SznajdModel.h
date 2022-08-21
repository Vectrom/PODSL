#pragma once
#include "Graph.h"
#include "ModelBase.h"

namespace PODSL
{
    class SznajdModel : public ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph);
        virtual ModelType getModelType() const;
    };
}