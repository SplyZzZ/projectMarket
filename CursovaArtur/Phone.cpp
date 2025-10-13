#include "Phone.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>

Phone::Phone() : Product()
{
    model = " ";
}

Phone::~Phone() {}

void Phone::GetInformationProduct() const noexcept
{
    Product::GetInformationProduct();

    UIConsoleColor::printTextUseColor("Модель: ", UIConsoleColor::Color::Cyan);
    std::cout << model << "\n";
}

void Phone::SetInformationProduct() noexcept
{
    Product::SetInformationProduct();

    UIConsoleColor::printTextUseColor("Введіть модель телефону: ", UIConsoleColor::Color::Yellow);
    model = ConsoleHelper::readLine();

    UIConsoleColor::printTextUseColor("✅ Модель успішно додана!\n", UIConsoleColor::Color::Green);
}
