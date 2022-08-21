#pragma once

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4458 4459)
#endif

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <string>

namespace podsl
{
    struct vertex_info
    {
        std::string index;
        int label;
    };

    class Graph
    {
    public:
        void load(const std::string& filePath);
        void save(const std::string& filePath) const;
        size_t getNumberOfVertices() const;
        std::string getIndex(size_t index) const;
        int getOpinion(size_t index) const;
        void setOpinion(size_t index, int opinion);
        std::set<size_t> getAdjacentVerticesIndexes(size_t index) const;
        size_t getRandomVertexIndex() const;
        size_t getRandomAdjacentVertexIndex(size_t index) const;
        bool hasAdjacentVertices(size_t index) const;
        bool hasConsensus() const;
        double getAverageOpinion() const;

    private:
        boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, vertex_info> _graph;
        boost::dynamic_properties _properties;
    };
}