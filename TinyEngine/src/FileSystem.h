#pragma once
#include <string>
#include <vector>

#include "Core.h"

namespace TE
{
    class TE_API FileSystem
    {
    public:
        static std::string ReadFile(const char* path);
        static std::string ReadFile(std::string path);
        static std::vector<float> FileToFloatVector(const std::string& str);
        static std::vector<float> FileToFloatVector(const char* path);
        static std::vector<float> ParseToFloatVector(const std::string& str);

    private:    
        static std::stringstream ReadFileToStringStream(const char* path);
    };
}

