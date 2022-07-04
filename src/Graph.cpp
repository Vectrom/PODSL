#include <Graph.h>

bool Graph::Load(const std::string& filePath)
{
    boost::property_map<graph_t, boost::vertex_name_t>::type name =
        get(boost::vertex_name, _graph);
    _properties.property("node_id", name);

    boost::property_map<graph_t, boost::vertex_color_t>::type opinion =
        get(boost::vertex_color, _graph);
    _properties.property("label", opinion);

    std::ifstream graphStream(filePath, std::ifstream::in);
    if (graphStream.fail())
        return false;

    return boost::read_graphviz(graphStream, _graph, _properties);
}

bool Graph::Save(const std::string& filePath)
{
    std::ofstream graphStream(filePath, std::ofstream::out);
    if (graphStream.fail())
        return false;

    boost::write_graphviz_dp(graphStream, _graph, _properties);

    graphStream.close();
    return true;
}