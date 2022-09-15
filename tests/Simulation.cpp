#include <gtest/gtest.h>
#include <filesystem>
#include "MajorityModel.h"
#include "SznajdModel.h"
#include "QVoterModel.h"
#include "VoterModel.h"
#include "PODSLEnums.h"
#include "Simulation.h"
#include "TestUtils.h"

using namespace podsl;

//only save result without check
TEST(Simulation, SimpleSimulation)
{
    Graph graph;

    ASSERT_NO_THROW(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSimulation/";
    std::filesystem::create_directory(tempDir);

    VoterModel model;
    Simulation simulation;
    simulation.setModel(model);
    simulation.setGraph(graph);
    simulation.startSimulation();

    graph = simulation.getGraph();
    ASSERT_NO_THROW(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");
    std::filesystem::remove_all(tempDir);
}

//only save result without check
TEST(Simulation, SimpleSznajdSimulation)
{
    Graph graph;

    ASSERT_NO_THROW(graph.load(TestUtils::getExamplesDir("simpleGraph.graphml")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSznajdSimulation/";
    std::filesystem::create_directory(tempDir);

    Simulation simulation;
    simulation.setModel(SznajdModel());
    simulation.setGraph(graph);
    simulation.startSimulation();

    graph = simulation.getGraph();
    ASSERT_NO_THROW(graph.save(tempDir + "test.graphml"));
    simulation.saveResultInfoToFile(tempDir + "result.json");
    std::filesystem::remove_all(tempDir);
}

TEST(Simulation, SaveResultInfoToFile)
{
    Graph graph;

    ASSERT_NO_THROW(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSave/";
    std::filesystem::create_directory(tempDir);

    VoterModel model;
    Simulation simulation;
    simulation.setModel(model);
    simulation.setGraph(graph);
    simulation.enableAverageOpinion();
    simulation.startSimulation();

    simulation.saveResultInfoToFile(tempDir + "result.json");
    std::filesystem::remove_all(tempDir);
}

TEST(Simulation, BasicVoterSimulationFromConfig)
{
    const std::string pathToConfigFile = TestUtils::saveConfigFile("testConfig.json", ModelType::Voter, TestUtils::getExamplesDir("simpleGraph.dot"), 100, true, false);
    
    Simulation simulation;
    ASSERT_NO_THROW(simulation.readConfig(pathToConfigFile));
    simulation.startSimulation();

    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/BasicVoterSimulationFromConfig/";
    std::filesystem::create_directory(tempDir);

    const Graph& graph = simulation.getGraph();
    ASSERT_NO_THROW(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");

    std::filesystem::remove(pathToConfigFile);
    std::filesystem::remove_all(tempDir);
}

TEST(Simulation, MajoritySimulationWithParameterFromConfig)
{
    TestUtils::ModelParams modelParams;
    modelParams.groupSize = 2;
    const std::string pathToConfigFile = TestUtils::saveConfigFile("testConfig.json", ModelType::Majority, TestUtils::getExamplesDir("simpleGraph.dot"), 50, true, true, modelParams);

    Simulation simulation;
    ASSERT_NO_THROW(simulation.readConfig(pathToConfigFile));
    simulation.startSimulation();

    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/MajoritySimulationWithParameterFromConfig/";
    std::filesystem::create_directory(tempDir);

    const Graph& graph = simulation.getGraph();
    ASSERT_NO_THROW(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");

    std::filesystem::remove(pathToConfigFile);
    std::filesystem::remove_all(tempDir);
}

TEST(Simulation, MajoritySimulationOnRegularSquare)
{
    MajorityModel model(5);

    Graph graph;
    ASSERT_NO_THROW(graph.load(TestUtils::getExamplesDir("regularSquare.dot")));

    Simulation simulation;
    simulation.setModel(model);
    simulation.setGraph(graph);
    simulation.enableAverageOpinion();
    simulation.enableCountingOpinions();
    simulation.startSimulation();

    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/MajoritySimulationOnRegularSquare/";
    std::filesystem::create_directory(tempDir);

    graph = simulation.getGraph();
    ASSERT_NO_THROW(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");

    std::filesystem::remove_all(tempDir);
}

TEST(Simulation, SimpleQVoterimulation)
{
    Graph graph;

    ASSERT_NO_THROW(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testQVoterSimulation/";
    std::filesystem::create_directory(tempDir);

    Simulation simulation;
    simulation.setModel(QVoterModel(1));
    simulation.setGraph(graph);
    simulation.enableAverageOpinion();
    simulation.setMaxIterations(100);
    simulation.startSimulation();

    graph = simulation.getGraph();
    ASSERT_NO_THROW(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");
    std::filesystem::remove_all(tempDir);
}
