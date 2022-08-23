#pragma once
#include "ModelBase.h"

namespace podsl
{
    class QVoterModel : public ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph) override;
        virtual ModelType getModelType() const override;
    };
}