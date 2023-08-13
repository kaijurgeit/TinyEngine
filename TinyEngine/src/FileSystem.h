#pragma once
#include "Core.h"

#include <string>
#include <vector>

namespace TE
{
    class TE_API FileSystem
    {
    public:
        static std::string ReadFile(const char* path);
        static std::vector<float> FileToFloatVector(const char* path);
        static std::vector<float> ParseToFloatVector(const std::string& string);
        static bool Foo();
        static bool Bar() { return true; }

    private:    
        static std::stringstream ReadFileToStringStream(const char* path);
    };
}

