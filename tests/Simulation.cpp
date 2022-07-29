#include <gtest/gtest.h>
#include <filesystem>
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

    graph = model.getGraph();
    ASSERT_TRUE(graph.save(tempDir + "test.dot"));
    std::filesystem::remove_all(tempDir);
}