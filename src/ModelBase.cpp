#include "ModelBase.h"
#include <boost/graph/adjacency_list.hpp>
#include <array>

// it is only test method to check boost::graph linking
bool ModelBase::testMethod()
{
    enum { topLeft, topRight, bottomRight, bottomLeft };

    std::array<std::pair<int, int>, 4> edges{ {
                                                     std::make_pair(topLeft, topRight),
                                                     std::make_pair(topRight, bottomRight),
                                                     std::make_pair(bottomRight, bottomLeft),
                                                     std::make_pair(bottomLeft, topLeft)
                                             } };

    typedef boost::adjacency_list<boost::setS, boost::vecS,
        boost::undirectedS> graph;
    graph g{ edges.begin(), edges.end(), 4 };
    return g.m_edges.size() == 4;
}