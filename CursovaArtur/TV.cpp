#include "TV.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>

TV::TV() : Product()
{
    resolution = " ";
}

TV::~TV() {}

void TV::GetInformationProduct() const noexcept
{
    Product::GetInformationProduct();

    UIConsoleColor::printTextUseColor("Розмір екрану: ", UIConsoleColor::Color::Cyan);
    std::cout << resolution << "\n";
}

void TV::SetInformationProduct() noexcept
{
    Product::SetInformationProduct();

    UIConsoleColor::printTextUseColor("Введіть розмір екрану: ", UIConsoleColor::Color::Yellow);
    resolution = ConsoleHelper::readLine();

    UIConsoleColor::printTextUseColor("✅ Телевізор успішно додано!\n", UIConsoleColor::Color::Green);
}
