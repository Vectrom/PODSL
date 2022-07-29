#pragma once

#pragma warning(push)
#pragma warning(disable : 4458 4459)
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#pragma warning(pop)

#include <string>

struct vertex_info
{
    std::string index;
    int label;
};

class Graph
{
public:
    bool load(const std::string& filePath);
    bool save(const std::string& filePath);
    size_t getNumberOfVertices() const;
    int getOpinion(size_t index) const;
    void setOpinion(size_t index, int opinion);
    std::set<size_t> getAdjacentVerticesIndexes(size_t index) const;
    size_t getRandomVertexIndex() const;
    size_t getRandomAdjacentVertexIndex(size_t index) const;
    bool hasAdjacentVertices(size_t index) const;
    bool hasConsensus() const;

private:
    boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, vertex_info> _graph;
    boost::dynamic_properties _properties;
};
