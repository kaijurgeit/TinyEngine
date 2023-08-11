#include <gtest/gtest.h>
#include <ImportTest.h>

TEST(InitTests, Basic)
{
    EXPECT_TRUE(true);
}

TEST(InitTests, ClassDllImport)
{    
    EXPECT_TRUE(TE::ClassImportTest::ClassDllImportTest());
}

TEST(InitTests, DllImport)
{    
    EXPECT_TRUE(TE::DllImportTest());
}