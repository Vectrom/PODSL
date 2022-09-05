#pragma once
#include <boost/property_map/dynamic_property_map.hpp>
#include <iostream>

class PajekParser
{
    template <typename MutableGraph>
    static void read_graphml(std::istream& in, MutableGraph& g, boost::dynamic_properties& dp)
    {
        mutate_graph_impl< MutableGraph > mg(g, dp)
    }
};