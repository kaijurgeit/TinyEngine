#include "FileSystem.h"

#include <fstream>
#include <iostream>
#include <sstream>


namespace TE
{
    std::string FileSystem::ReadFile(const char* path)
    {        
        return ReadFileToStringStream(path).str();
    }

    std::vector<float> FileSystem::FileToFloatVector(const char* path)
    {
        return ParseToFloatVector(ReadFile(path));
    }

    std::vector<float> FileSystem::ParseToFloatVector(const std::string& string)
    {        
        std::vector<float> data;
        return data;
    }

    bool FileSystem::Foo()
    {
        return  true;
    }

    std::stringstream FileSystem::ReadFileToStringStream(const char* path)
    {
        std::stringstream out;
        std::ifstream inFileStream;
        inFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            inFileStream.open(path);
            out << inFileStream.rdbuf();
        }
        catch (std::ifstream::failure& e)
        {
            std::cerr << e.what() << "\n";
        }

        return out;
    }
}

