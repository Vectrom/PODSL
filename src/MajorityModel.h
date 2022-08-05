#pragma once
#include "ModelBase.h"

class MajorityModel : public ModelBase
{
public:
    MajorityModel(const Graph& graph);
    virtual std::map<std::string, int> calculateOneStep();
};