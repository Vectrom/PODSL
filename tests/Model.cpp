#include <gtest/gtest.h>
#include "PODSLEnums.h"
#include "MajorityModel.h"
#include "SznajdModel.h"
#include "VoterModel.h"

TEST(Model, ModelType) {
    EXPECT_EQ(MajorityModel().getModelType(), ModelType::Majority);
    EXPECT_EQ(SznajdModel().getModelType(), ModelType::Sznajd);
    EXPECT_EQ(VoterModel().getModelType(), ModelType::Voter);

    class TestModel : public ModelBase
    {
    public:
        std::map<std::string, int> calculateOneStep(Graph&) { return {}; }
    };

    EXPECT_EQ(TestModel().getModelType(), ModelType::Custom);

}