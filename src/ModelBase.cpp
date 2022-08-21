#include "ModelBase.h"
#include "PODSLEnums.h"

using namespace PODSL;

ModelType ModelBase::getModelType() const
{
    return ModelType::Custom;
}
