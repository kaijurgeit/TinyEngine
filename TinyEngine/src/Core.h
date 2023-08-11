#pragma once

#ifdef TE_BUILD_DLL
    #define TE_API __declspec(dllexport)
#else
    #define TE_API __declspec(dllimport)
#endif