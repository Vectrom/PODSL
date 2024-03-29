#pragma once
#include "Graph.h"

namespace podsl
{
    enum class ModelType;

    class ModelBase
    {
    public:
        virtual std::map<std::string, int> calculateOneStep(Graph& graph) = 0;
        virtual ModelType getModelType() const;
        virtual ~ModelBase() = default;
    };

    template <typename T>
    concept DerivedFromModelBase = std::is_base_of_v<ModelBase, T>;
}