#pragma once

#include <string>

namespace podsl { enum class ModelType; }

using namespace podsl;

namespace TestUtils
{
    struct ModelParams
    {
        uint64_t groupSize = 0;

        bool operator!=(ModelParams mp)
        {
            return mp.groupSize != groupSize;
        }
    };

    std::string getExamplesDir(const std::string& name);
    std::string saveConfigFile(const std::string& fileName, ModelType modelType, const std::string& pathToGraph, uint64_t maxIterations = 0, bool averageOpinion = false, bool printInfoAboutChanges = false, ModelParams modelParams = {});
}