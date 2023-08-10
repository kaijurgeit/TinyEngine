#include <iostream>
#include "MyLibrary.h"

namespace TE
{
    __declspec(dllimport) int Square(int x);
}

int main()
{
    std::cout << "Hello Application!" << "\n";
    std::cout << "TE::Square(8) = " << TE::Square(8) << "\n";
}
