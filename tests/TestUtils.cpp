#include "TestUtils.h"
#include "TestUtilsConstexpr.h"
#include "PODSLEnums.h"

#include <filesystem>
#include <fstream>

using namespace podsl;

std::string TestUtils::getExamplesDir(const std::string& name)
{
    return std::string(TestUtils::examplesDir) + '/' + name;
}

std::string TestUtils::saveConfigFile(const std::string& fileName, ModelType modelType, const std::string& pathToGraph, uint64_t maxIterations, bool averageOpinion, ModelParams modelParams)
{
    const std::string tempDir = std::filesystem::temp_directory_path().string();

    const std::string pathToConfig{ tempDir + '/' + fileName };
    std::ofstream configFile(pathToConfig);
    configFile << "{\n";
    configFile << "    \"model\": \"" << modelTypeToString(modelType) << "\",\n";
    if (modelParams != ModelParams{})
    {
        configFile << "    \"modelParams\": {\n";
        if (modelParams.groupSize != 0)
            configFile << "        \"groupSize\": " << modelParams.groupSize << "\n";
        configFile << "    },\n";
    }
    configFile << "    \"pathToGraph\": \"" << pathToGraph << "\",\n";
    if(maxIterations != 0)
        configFile << "    \"maxIterations\": " << maxIterations << ",\n";
    if(averageOpinion)
        configFile << "    \"averageOpinion\": " << std::boolalpha << averageOpinion << "\n";
    configFile << "}";
    configFile.close();

    return pathToConfig;
}
