#include "Product.h"
#include "FleshDrive.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>

Product::Product() : price(0), size(0), name(" "), description(" ")
{
    ID = ++Unical;
}

Product::~Product() {}

void Product::GetInformationProduct() const noexcept
{
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("ІНФОРМАЦІЯ ПРО ТОВАР\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    UIConsoleColor::printTextUseColor("ID: ", UIConsoleColor::Color::Cyan);
    std::cout << ID << "\n";

    UIConsoleColor::printTextUseColor("Ціна: ", UIConsoleColor::Color::Cyan);
    std::cout << price << " ₴\n";

    UIConsoleColor::printTextUseColor("Розмір: ", UIConsoleColor::Color::Cyan);
    std::cout << size << " ГБ\n";

    UIConsoleColor::printTextUseColor("Назва: ", UIConsoleColor::Color::Cyan);
    std::cout << name << "\n";

    UIConsoleColor::printTextUseColor("Опис: ", UIConsoleColor::Color::Cyan);
    std::cout << description << "\n";

    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
}

void Product::SetInformationProduct() noexcept
{
    UIConsoleColor::printTextUseColor("Введіть ціну товару (₴): ", UIConsoleColor::Color::Yellow);
    ConsoleHelper::readNumber(price);

    UIConsoleColor::printTextUseColor("Введіть розмір (ГБ): ", UIConsoleColor::Color::Yellow);
    ConsoleHelper::readNumber(size);

    UIConsoleColor::printTextUseColor("Введіть назву товару: ", UIConsoleColor::Color::Yellow);
    name = ConsoleHelper::readLine();

    UIConsoleColor::printTextUseColor("Введіть опис товару: ", UIConsoleColor::Color::Yellow);
    description = ConsoleHelper::readLine();

}

int Product::GetID() const noexcept
{
    return ID;
}

double Product::GetPrice() const noexcept
{
    return price;
}

size_t Product::GetSize() const noexcept
{
    return size;
}

std::string Product::GetName() const noexcept
{
    return name;
}

int Product::Unical = 0;
