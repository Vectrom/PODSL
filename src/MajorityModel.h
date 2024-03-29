#pragma once
#include "ModelBase.h"

namespace podsl
{
    class MajorityModel : public ModelBase
    {
    public:
        MajorityModel(uint64_t groupSize);
        virtual std::map<std::string, int> calculateOneStep(Graph& graph) override;
        virtual ModelType getModelType() const override;
        void checkMajorityModelRequirements(const Graph& graph) const;
    private:
        uint64_t _groupSize;
    };
}