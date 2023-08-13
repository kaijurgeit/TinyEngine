#include <gtest/gtest.h>
#include <FileSystem.h>

struct FileSystemTest : public ::testing::Test
{
    std::vector<float> exp_floatVector = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
    };  
};

TEST_F(FileSystemTest, ParseToFloatVector_Str0)
{
    const std::string str = "0.5,  0.5, -0.5";
    const std::vector<float> floatVector = TE::FileSystem::ParseToFloatVector(str);
    bool foo = TE::FileSystem::Foo();
    EXPECT_EQ(exp_floatVector, floatVector);
}


TEST_F(FileSystemTest, ParseToFloatVector_Str1)
{
    const std::string str =
        "// positions          // normals           // texture coords"
        "-0.5f, -0.5f, -0.5f,"
        "\n 0.5f, -0.5f, -0.5f,\n ";
    const std::vector<float> floatVector = TE::FileSystem::ParseToFloatVector(str);
    EXPECT_EQ(exp_floatVector, floatVector);
}