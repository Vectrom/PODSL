#include "TestUtils.h"
#include "TestUtilsConstexpr.h"

const std::string TestUtils::getExamplesDir(const std::string& name)
{
    return std::string(TestUtils::examplesDir) + '/' + name;
}
