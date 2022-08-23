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

std::string TestUtils::saveConfigFile(const std::string& fileName, ModelType modelType, const std::string& pathToGraph, uint64_t maxIterations, bool averageOpinion, bool printInfoAboutChanges, ModelParams modelParams)
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
    configFile << "    \"pathToGraph\": \"" << pathToGraph << "\"";
    if(maxIterations != 0)
        configFile << ",\n" << "    \"maxIterations\": " << maxIterations;
    if(averageOpinion)
        configFile << ",\n" << "    \"averageOpinion\": " << std::boolalpha << averageOpinion;
    if (printInfoAboutChanges)
        configFile << ",\n" << "    \"printInfoAboutChanges\": " << std::boolalpha << printInfoAboutChanges << "\n";
    configFile << "}";
    configFile.close();

    return pathToConfig;
}
