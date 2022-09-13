#include "Graph.h"
#include "Exception.h"
#include <boost/graph/graphml.hpp>
#include <boost/graph/graph_utility.hpp>
#include <filesystem>
#include <numeric>
#include <random>

using namespace podsl;

void Graph::load(const std::string& filePath)
{
    const std::string extension = std::filesystem::path(filePath).extension().string();
    if (extension == ".dot")
        loadFromGraphviz(filePath);
    else if (extension == ".xml")
        loadFromGraphml(filePath);
    else
        throw Exception(ErrorCode::ExtensionNotSupported, "You can load only .dot (Graphviz) and .xml (GraphML) files.");
}

void Graph::save(const std::string& filePath) const
{
    const std::string extension = std::filesystem::path(filePath).extension().string();
    if (extension == ".dot")
        saveToGraphviz(filePath);
    else if (extension == ".xml")
        saveToGraphml(filePath);
    else
        throw Exception(ErrorCode::ExtensionNotSupported, "You can save only to .dot (Graphviz) and .xml (GraphML) files.");
}

void Graph::loadFromGraphviz(const std::string& filePath)
{
    _properties.property("node_id", boost::get(&vertexInfo::index, _graph));

    _properties.property("label", boost::get(&vertexInfo::label, _graph));

    std::ifstream graphStream(filePath, std::ifstream::in);
    if (graphStream.fail())
        throw Exception(ErrorCode::ReadingFileError, "Path to file: " + filePath);

    if (!boost::read_graphviz(graphStream, _graph, _properties))
        throw Exception(ErrorCode::ParsingGraphvizError);
}

void Graph::saveToGraphviz(const std::string& filePath) const
{
    std::ofstream graphStream(filePath, std::ofstream::out);
    if (graphStream.fail())
        throw Exception(ErrorCode::SavingFileError, "Path to file: " + filePath);

    boost::write_graphviz_dp(graphStream, _graph, _properties);

    graphStream.close();
}

void Graph::loadFromGraphml(const std::string& filePath)
{
    _properties.property("node_id", boost::get(&vertexInfo::index, _graph));

    _properties.property("label", boost::get(&vertexInfo::label, _graph));

    std::ifstream graphStream(filePath, std::ifstream::in);
    if (graphStream.fail())
        throw Exception(ErrorCode::ReadingFileError, "Path to file: " + filePath);

    boost::read_graphml(graphStream, _graph, _properties);
}

void Graph::saveToGraphml(const std::string& filePath) const
{
    std::ofstream graphStream(filePath, std::ofstream::out);
    if (graphStream.fail())
        throw Exception(ErrorCode::SavingFileError, "Path to file: " + filePath);

    boost::write_graphml(graphStream, _graph, _properties);

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

size_t Graph::getNumberOfAdjacentVertices(size_t index) const
{
    auto adjacentVertices = getAdjacentVerticesIndexes(index);
    return adjacentVertices.size();
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
    int sum = std::accumulate(_graph.m_vertices.begin(), _graph.m_vertices.end(), 0,
        [](int a, const auto& vertex) {
        return a + vertex.m_property.label;
    });

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

size_t Graph::getNumberOfPositiveOpinions() const
{
    return std::count_if(_graph.m_vertices.begin(), _graph.m_vertices.end(), [this](const auto& vertex) {
        return vertex.m_property.label == 1; });
}

size_t Graph::getNumberOfNegativeOpinions() const
{
    return std::count_if(_graph.m_vertices.begin(), _graph.m_vertices.end(), [this](const auto& vertex) {
        return vertex.m_property.label == -1; });
}
