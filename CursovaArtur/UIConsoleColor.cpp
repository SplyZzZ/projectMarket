#include "UIConsoleColor.h"
#include <iostream>
std::string_view UIConsoleColor::setColor(UIConsoleColor::Color color)
{
    switch (color)
    {
    case UIConsoleColor::Color::Reset:
    {
        return "\033[0m";
        break;
    }
    case UIConsoleColor::Color::Cyan:
    {
        return "\033[36m";
        break;
    }
    case UIConsoleColor::Color::Green:
    {
        return "\033[32m";
        break;
    }
    case UIConsoleColor::Color::Red:
    {
        return "\033[31m";
        break;
    }
    case UIConsoleColor::Color::Yellow:
    {
        return "\033[33m";
        break;
    }
    case UIConsoleColor::Color::Magenta:
    {
        return "\033[35m";
        break;
    }
    case UIConsoleColor::Color::Blue:
    {
        return  "\033[34m";
        break;
    }
    default:
    {
        return "\033[0m";
        break;
    }
    }
}


