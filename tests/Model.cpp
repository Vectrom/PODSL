#include <gtest/gtest.h>
#include "PODSLEnums.h"
#include "MajorityModel.h"
#include "QVoterModel.h"
#include "SznajdModel.h"
#include "VoterModel.h"

using namespace podsl;
TEST(Model, ModelType) {
    EXPECT_EQ(MajorityModel(5).getModelType(), ModelType::Majority);
    EXPECT_EQ(SznajdModel().getModelType(), ModelType::Sznajd);
    EXPECT_EQ(QVoterModel(3).getModelType(), ModelType::QVoter);
    EXPECT_EQ(VoterModel().getModelType(), ModelType::Voter);

    class TestModel : public ModelBase
    {
    public:
        std::map<std::string, int> calculateOneStep(Graph&) { return {}; }
    };

    EXPECT_EQ(TestModel().getModelType(), ModelType::Custom);

}