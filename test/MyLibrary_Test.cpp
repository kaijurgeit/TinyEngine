#include <gtest/gtest.h>

#include "MyLibrary.h"

struct ExampleTests : public ::testing::Test
{
    int x = 4;

    virtual void SetUp() override
    {
    printf("SetUp ExampleTests\n");
    }

    virtual void TearDown() override
    {
    printf("TearDown ExampleTests\n");
    }
};

TEST_F(ExampleTests, Square)
{
    int exp_square = x * x;
    EXPECT_EQ(
        exp_square,
        TE::Square(x)
    );
    // EXPECT_TRUE(false);
}