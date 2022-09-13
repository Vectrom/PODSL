#pragma once
#include "ModelBase.h"

namespace podsl
{
    class QVoterModel : public ModelBase
    {
    public:
        QVoterModel(uint64_t q/*, double probability = 0*/);
        virtual std::map<std::string, int> calculateOneStep(Graph& graph) override;
        virtual ModelType getModelType() const override;
    private:
        uint64_t _q;
        /*double _probability; */
    };
}