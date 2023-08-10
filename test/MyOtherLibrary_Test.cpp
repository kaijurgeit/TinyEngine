#include <gtest/gtest.h>

#include "MyOtherLibrary.h"

TEST(OtherTests, Foo)
{
    EXPECT_EQ(
        49,
        TE::Foo()
    );
    // EXPECT_TRUE(false);
}