#include "exercise.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>

Exercise::Exercise() : Product()
{
    type = " ";
}

Exercise::~Exercise() {}

void Exercise::GetInformationProduct() const noexcept
{
    Product::GetInformationProduct();

    UIConsoleColor::printTextUseColor("Тип зарядки: ", UIConsoleColor::Color::Cyan);
    std::cout << type << "\n";
}

void Exercise::SetInformationProduct() noexcept
{
    Product::SetInformationProduct();

    UIConsoleColor::printTextUseColor("Введіть тип зарядки: ", UIConsoleColor::Color::Yellow);
    type = ConsoleHelper::readLine();

    UIConsoleColor::printTextUseColor("✅ Тип зарядки успішно додано!\n", UIConsoleColor::Color::Green);
}
