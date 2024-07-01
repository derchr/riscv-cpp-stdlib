#include "uart.h"

#include <iostream>
#include <queue>
#include <string>

int main()
{
    std::queue<std::string> strings;
    strings.emplace("Hello");
    strings.emplace("World!");
    
    while (!strings.empty())
    {
        std::cout << strings.front() << "\n";
        strings.pop();
    }

    return 0;
}
