#pragma once

#pragma warning(push)
#pragma warning(disable : 4458 4459)
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#pragma warning(pop)

#include <string>

// Vertex properties
typedef boost::property < boost::vertex_name_t, std::string,
    boost::property < boost::vertex_color_t, int > > vertex_p;
// Edge properties
typedef boost::property < boost::edge_weight_t, double > edge_p;
// Graph properties
typedef boost::property < boost::graph_name_t, std::string > graph_p;
// adjacency_list-based type
typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS,
    vertex_p, edge_p, graph_p > graph_t;

class Graph
{
public:
    bool Load(const std::string& filePath);
    bool Save(const std::string& filePath);

private:
    boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, vertex_p, edge_p, graph_p> _graph;
    boost::dynamic_properties _properties;
};
