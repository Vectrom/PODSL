#include <gtest/gtest.h>
#include <filesystem>
#include "Graph.h"
#include "TestUtils.h"

TEST(Graph, LoadGraph)
{
    Graph graph;

    ASSERT_TRUE(graph.Load(TestUtils::getExamplesDir("simpleGraph.dot")));
    std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSave/";
    std::filesystem::create_directory(tempDir);
    ASSERT_TRUE(graph.Save(tempDir + "test.dot"));
    std::filesystem::remove_all(tempDir);
}