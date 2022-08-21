#include "ModelBase.h"
#include "PODSLEnums.h"

using namespace podsl;

ModelType ModelBase::getModelType() const
{
    return ModelType::Custom;
}
