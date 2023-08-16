#include "FileSystem.h"

#include <fstream>
#include <iostream>
#include <regex>
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

    std::vector<float> FileSystem::ParseToFloatVector(const std::string& str)
    {        
        std::vector<float> data;
    
        const std::regex regex("[+-]?([0-9]*[.])?[0-9]+");
        std::smatch matches;

        std::ifstream istream;
        float x;

        std::string::const_iterator searchStart( str.cbegin() );
        while ( std::regex_search( searchStart, str.cend(), matches, regex ) )
        {
            data.push_back(std::stod(matches[0]));
            searchStart = matches.suffix().first;
        }
    
        return data;
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

