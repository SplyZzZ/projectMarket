#include <string>
#include <iostream>
namespace UIConsoleColor
{
    enum class Color
    {
        Reset,
        Cyan,
        Green,
        Red,
        Yellow,
        Magenta,
        Blue
    };
    std::string_view setColor(UIConsoleColor::Color color);

    inline void printTextUseColor(std::string_view text, Color color)
    {
        std::cout << setColor(color) << text << setColor(Color::Reset);
    }
}