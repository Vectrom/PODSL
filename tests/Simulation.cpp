#include <gtest/gtest.h>
#include <filesystem>
#include "MajorityModel.h"
#include "Simulation.h"
#include "TestUtils.h"

TEST(Simulation, SimpleSimulation)
{
    Graph graph;

    //ASSERT_TRUE(graph.Load(TestUtils::getExamplesDir("simpleGraph.dot")));
    //const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSave/";
    //std::filesystem::create_directory(tempDir);
    //ASSERT_TRUE(graph.Save(tempDir + "test.dot"));
    //std::filesystem::remove_all(tempDir);
    MajorityModel model;
    Simulation(model, graph);
}