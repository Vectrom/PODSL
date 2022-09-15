#pragma once

#include <string>
#include <vector>

namespace podsl
{
    class StringUtils
    {
    public:
        static std::vector<std::string> split(const std::string& string, char delimiter);
    };
}