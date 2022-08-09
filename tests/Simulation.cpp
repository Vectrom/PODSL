#include <gtest/gtest.h>
#include <filesystem>
#include "SznajdModel.h"
#include "VoterModel.h"
#include "Simulation.h"
#include "TestUtils.h"

//only save result without check
TEST(Simulation, SimpleSimulation)
{
    Graph graph;

    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSimulation/";
    std::filesystem::create_directory(tempDir);

    VoterModel model(graph);
    Simulation simulation(model);
    simulation.startSimulation();

    graph = simulation.getModel().getGraph();
    ASSERT_TRUE(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");
    //Bstd::filesystem::remove_all(tempDir);
}

//only save result without check
TEST(Simulation, SimpleSznajdSimulation)
{
    Graph graph;

    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSznajdSimulation/";
    std::filesystem::create_directory(tempDir);

    SznajdModel model(graph);
    Simulation simulation(model);
    simulation.startSimulation();

    graph = simulation.getModel().getGraph();
    ASSERT_TRUE(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");
    //std::filesystem::remove_all(tempDir);
}

TEST(Simulation, SaveResultInfoToFile)
{
    Graph graph;

    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSave/";
    std::filesystem::create_directory(tempDir);

    VoterModel model(graph);
    Simulation simulation(model);
    simulation.enableAverageOpinion();
    simulation.startSimulation();

    simulation.saveResultInfoToFile(tempDir + "result.json");
    //std::filesystem::remove_all(tempDir);
}

TEST(Simulation, SimulationFromConfig)
{
    Simulation simulation(TestUtils::getExamplesDir("simpleConfig.json"));
    simulation.startSimulation();

    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testConfig/";
    std::filesystem::create_directory(tempDir);

    const Graph& graph = simulation.getModel().getGraph();
    ASSERT_TRUE(graph.save(tempDir + "test.dot"));
    simulation.saveResultInfoToFile(tempDir + "result.json");
    EXPECT_TRUE(false);
    //std::filesystem::remove_all(tempDir);
}