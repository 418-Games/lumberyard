
#include <AzTest/AzTest.h>

class FourEighteenGamesTest
    : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(FourEighteenGamesTest, SanityTest)
{
    ASSERT_TRUE(true);
}

AZ_UNIT_TEST_HOOK();
