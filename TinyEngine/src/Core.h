#pragma once

#include <glad/glad.h>
// #include <GLFW/glfw3.h>

#ifdef TE_BUILD_DLL
    #define TE_API __declspec(dllexport)
#else
    #define TE_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#define TE_ASSERT(Expr, Msg) \
    TeAssert_(Expr, #Expr, Msg, __FILE__, __LINE__)
#endif
#include <iostream>

inline void TeAssert_(bool expr, const char* exprStr, const char* msg, const char* file, int line)
{
    if (!expr)
    {
        std::cerr << file << "(" << line << "): TE Assertion failed: " << exprStr;
        abort();
    }
}
