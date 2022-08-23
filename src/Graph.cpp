#include "Graph.h"
#include "Exception.h"
#include <boost/graph/graph_utility.hpp>
#include <random>

using namespace podsl;

void Graph::load(const std::string& filePath)
{
    _properties.property("node_id", boost::get(&vertex_info::index, _graph));

    _properties.property("label", boost::get(&vertex_info::label, _graph));

    std::ifstream graphStream(filePath, std::ifstream::in);
    if (graphStream.fail())
        throw Exception(ErrorCode::ReadingFileError, "Path to file: " + filePath);

    if (!boost::read_graphviz(graphStream, _graph, _properties))
        throw Exception(ErrorCode::ParsingGraphvizError);
}

void Graph::save(const std::string& filePath) const
{
    std::ofstream graphStream(filePath, std::ofstream::out);
    if (graphStream.fail())
        throw Exception(ErrorCode::SavingFileError, "Path to file: " + filePath);

    boost::write_graphviz_dp(graphStream, _graph, _properties);

    graphStream.close();
}

size_t Graph::getNumberOfVertices() const
{
    return _graph.m_vertices.size();
}

size_t Graph::getNumberOfEdges() const
{
    return _graph.m_edges.size();
}

std::string Graph::getIndex(size_t index) const
{
    return _graph[index].index;
}

int Graph::getOpinion(size_t index) const
{
    return _graph[index].label;
}

void Graph::setOpinion(size_t index, int opinion)
{
    _graph[index].label = opinion;
}

std::set<size_t> Graph::getAdjacentVerticesIndexes(size_t index) const
{
    auto adjacentVertices = boost::adjacent_vertices(index, _graph);
    return std::set<size_t>(adjacentVertices.first, adjacentVertices.second);
}

size_t Graph::getRandomVertexIndex() const
{
    std::uniform_int_distribution<std::mt19937::result_type> udist(0, static_cast<unsigned int>(getNumberOfVertices() - 1));
    std::random_device rd;
    std::mt19937 rng(rd());

    return udist(rng);
}

size_t Graph::getRandomAdjacentVertexIndex(size_t index) const
{
    std::set<size_t> adjacentVertices = getAdjacentVerticesIndexes(index);
    std::uniform_int_distribution<std::mt19937::result_type> udist(0, static_cast<unsigned int>(adjacentVertices.size() - 1));
    std::random_device rd;
    std::mt19937 rng(rd());

    auto it = adjacentVertices.begin();
    std::advance(it, udist(rng));
    return *it;
}

bool Graph::hasAdjacentVertices(size_t index) const
{
    auto adjacentVertices = getAdjacentVerticesIndexes(index);
    return !adjacentVertices.empty();
}

bool Graph::hasConsensus() const
{
    int opinionInPreviousVertex = _graph[0].label;
    for(size_t i = 1; i < _graph.m_vertices.size(); i++)
    {
        if (_graph[i].label != opinionInPreviousVertex)
            return false;

        opinionInPreviousVertex = _graph[i].label;
    }
    return true;
}

double Graph::getAverageOpinion() const
{
    int sum = 0;
    for (const auto& vertex : _graph.m_vertices)
        sum += vertex.m_property.label;

    return static_cast<double>(sum) / getNumberOfVertices();
}

bool Graph::isComplete() const
{
    size_t numberOfVertices = getNumberOfVertices();
    if (getNumberOfEdges() != (numberOfVertices * (numberOfVertices-1) / 2))
        return false;

    if (hasSelfLoops())
        return false;

    return true;
}

bool podsl::Graph::hasSelfLoops() const
{
    for (const auto& edge : _graph.m_edges)
    {
        if (edge.m_source == edge.m_target)
            return true;
    }
    return false;
}
