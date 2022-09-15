#include "StringUtils.h"
#include <sstream>
using namespace podsl;

std::vector<std::string> StringUtils::split(const std::string& string, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream stringStream(string);
    std::string item;

    while (std::getline(stringStream, item, delimiter))
    {
        result.push_back(item);
    }

    return result;
}