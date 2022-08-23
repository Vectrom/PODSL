#pragma once
#include "Graph.h"
#include "ModelBase.h"

namespace podsl
{
    class VoterModel : public ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph) override;
        virtual ModelType getModelType() const override;
    };
}