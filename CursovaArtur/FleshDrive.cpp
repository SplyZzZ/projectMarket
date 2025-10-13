#include "FleshDrive.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>

FleshDrive::FleshDrive() : Product()
{
    sizeGB = 0;
}

FleshDrive::~FleshDrive() {}

void FleshDrive::GetInformationProduct() const noexcept
{
    Product::GetInformationProduct();

    UIConsoleColor::printTextUseColor("Обсяг пам’яті: ", UIConsoleColor::Color::Cyan);
    std::cout << sizeGB << " ГБ\n";
}

void FleshDrive::SetInformationProduct() noexcept
{
    Product::SetInformationProduct();

    UIConsoleColor::printTextUseColor("Введіть розмір флешки в гігабайтах: ", UIConsoleColor::Color::Yellow);
    ConsoleHelper::readNumber(sizeGB);

    UIConsoleColor::printTextUseColor("✅ Флешку успішно додано!\n", UIConsoleColor::Color::Green);
}
