#pragma once
#include "Exception.h"
#include "StringUtils.h"
#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <iostream>

namespace podsl
{
    class PajekParser
    {
    public:
        template <typename MutableGraph>
        static void readPajekNet(std::istream& in, MutableGraph& graph)
        {
            if (!in.good())
                throw Exception(ErrorCode::ParsingPajekError, "Error during parsing Pajek NET file.");

            std::map<std::string, MutableGraph::vertex_descriptor> vertices;
            bool readingVertices = false, readingEdges = false;

            for (std::string line; std::getline(in, line);)
            {
                std::vector<std::string> tokens = StringUtils::split(line, ' ');
                if (tokens.empty())
                    continue;
                
                boost::algorithm::to_lower(tokens[0]);
                if(tokens[0][0] == '*')
                {
                    readingVertices = false;
                    readingEdges = false;

                    if (tokens[0] == "*vertices")
                    {
                        readingVertices = true;
                        continue;
                    }
                    else if (tokens[0] == "*edges")
                    {
                        readingEdges = true;
                        continue;
                    }
                    else continue;
                }

                if (readingVertices)
                {
                    if (tokens.size() < 2)
                        throw Exception(ErrorCode::ParsingPajekError, "Error during parsing Pajek NET file.");

                    tokens[1].erase(std::remove(tokens[1].begin(), tokens[1].end(), '\"'));

                    vertices[tokens[0]] = addVertex(graph, tokens[0], std::stoi(tokens[1]));
                }
                else if (readingEdges)
                {
                    if (tokens.size() < 2)
                        throw Exception(ErrorCode::ParsingPajekError, "Error during parsing Pajek NET file.");

                    boost::add_edge(vertices[tokens[0]], vertices[tokens[1]], graph);
                }
            }
        }

        template <typename MutableGraph>
        static void writePajekNet(std::ostream& out, const MutableGraph& graph)
        {
            if (!out.good())
                throw Exception(ErrorCode::SavingFileError, "Error during saving Pajek NET file.");

            const auto& vertices = graph.m_vertices;
            if(!vertices.empty())
            {
                writeVertices(out, vertices);
            }

            const auto& edges = graph.m_edges;
            if (!edges.empty())
            {
                 writeEdges(out, graph, edges);
            }
        }

    private:
        template <typename MutableGraph>
        static auto addVertex(MutableGraph& graph, const std::string& index, int label)
        {
            const auto vertex = boost::add_vertex(graph);
            graph[vertex].index = index;
            graph[vertex].label = label;

            return vertex;
        }

        template <typename VerticesVector>
        static void writeVertices(std::ostream& out, const VerticesVector& vertices)
        {
            out << "*Vertices " << vertices.size() << '\n';
            for (const auto& vertex : vertices)
            {
                out << vertex.m_property.index << " \"" << vertex.m_property.label << '\"' << '\n';
            }
        }

        template <typename MutableGraph, typename EdgesVector>
        static void writeEdges(std::ostream& out, const MutableGraph& graph, const EdgesVector& edges)
        {
            out << "*Edges\n";
            for (const auto& edge : edges)
            {
                out << graph[edge.m_source].index << ' ' << graph[edge.m_target].index << '\n';
            }
        }
    };
}