#pragma once
#include "ModelBase.h"

namespace PODSL
{
    class QVoterModel : public ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph);
        virtual ModelType getModelType() const;
    };
}