#include <gtest/gtest.h>
#include <filesystem>
#include "Graph.h"
#include "TestUtils.h"

TEST(Graph, LoadGraph)
{
    Graph graph;

    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::string tempDir = std::filesystem::temp_directory_path().string() + "/testSave/";
    std::filesystem::create_directory(tempDir);
    ASSERT_TRUE(graph.save(tempDir + "test.dot"));
    std::filesystem::remove_all(tempDir);
}

TEST(Graph, GetNumberOfVertices)
{
    Graph graph;
    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    ASSERT_EQ(graph.getNumberOfVertices(), 4);
}

TEST(Graph, GetOpinion)
{
    Graph graph;
    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    ASSERT_EQ(graph.getOpinion(0), 1);
}

TEST(Graph, SetOpinion)
{
    Graph graph;
    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    ASSERT_EQ(graph.getOpinion(0), 1);
    graph.setOpinion(0, -1);
    ASSERT_EQ(graph.getOpinion(0), -1);
}

TEST(Graph, GetAdjacentVertices) {
    Graph graph;
    ASSERT_TRUE(graph.load(TestUtils::getExamplesDir("simpleGraph.dot")));
    const std::set<size_t> adjacentVertices = graph.getAdjacentVerticesIndexes(1);
    ASSERT_EQ(adjacentVertices, std::set<size_t>({0, 2, 3}));
}

