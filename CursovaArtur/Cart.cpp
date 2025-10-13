#include "Cart.h"
#include "Customer.h"
#include "UIConsoleColor.h"
#include <Windows.h>
#include <iostream>

Cart::Cart() : totalCount(0) {}

bool Cart::AddProduct(const std::unordered_map<std::string, std::shared_ptr<Category>>& other) noexcept
{
    if (other.empty())
    {
        UIConsoleColor::printTextUseColor("⚠️  Немає доступних категорій для вибору.\n", UIConsoleColor::Color::Red);
        return false;
    }

    UIConsoleColor::printTextUseColor("\n-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("                 ДОДАВАННЯ ТОВАРУ ДО КОШИКА\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    UIConsoleColor::printTextUseColor("Доступні категорії:\n", UIConsoleColor::Color::Yellow);
    for (const auto& [name, category] : other)
    {
        UIConsoleColor::printTextUseColor(" - ", UIConsoleColor::Color::Cyan);
        std::cout << name << "\n";
    }

    UIConsoleColor::printTextUseColor("\nВведіть назву категорії: ", UIConsoleColor::Color::Yellow);
    std::string option;
    std::cin.ignore();
    std::getline(std::cin, option);

    if (other.find(option) == other.end())
    {
        UIConsoleColor::printTextUseColor("❌ Такої категорії не існує!\n", UIConsoleColor::Color::Red);
        return false;
    }

    auto category = other.at(option);
    category->GetListProduct();

    UIConsoleColor::printTextUseColor("Введіть ID товару: ", UIConsoleColor::Color::Yellow);
    int towarID;
    std::cin >> towarID;

    try
    {
        auto product = category->GetProduct(towarID);
        productList.push_back(product);
        totalCount += product->GetPrice();
        UIConsoleColor::printTextUseColor("✅ Товар успішно додано до кошика!\n", UIConsoleColor::Color::Green);
        return true;
    }
    catch (const std::exception&)
    {
        UIConsoleColor::printTextUseColor("❌ Помилка: товар з таким ID не знайдено!\n", UIConsoleColor::Color::Red);
        return false;
    }
}

bool Cart::DeleteProduct() noexcept
{
    if (productList.empty())
    {
        UIConsoleColor::printTextUseColor("⚠️  Кошик порожній — немає що видаляти.\n", UIConsoleColor::Color::Red);
        return false;
    }

    UIConsoleColor::printTextUseColor("\n-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("                 ВИДАЛЕННЯ ТОВАРУ З КОШИКА\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    for (size_t i = 0; i < productList.size(); ++i)
    {
        UIConsoleColor::printTextUseColor(std::to_string(i + 1) + ". ", UIConsoleColor::Color::Cyan);
        productList[i]->GetInformationProduct();
    }

    UIConsoleColor::printTextUseColor("Введіть номер товару для видалення: ", UIConsoleColor::Color::Yellow);
    size_t option = 0;
    std::cin >> option;

    if (option == 0 || option > productList.size())
    {
        UIConsoleColor::printTextUseColor("❌ Невірний номер!\n", UIConsoleColor::Color::Red);
        return false;
    }

    totalCount -= productList[option - 1]->GetPrice();
    productList.erase(productList.begin() + (option - 1));

    UIConsoleColor::printTextUseColor("✅ Товар успішно видалено з кошика!\n", UIConsoleColor::Color::Green);
    return true;
}

double Cart::ResulPrice() const noexcept
{
    return totalCount;
}

std::shared_ptr<Product> Cart::GetElementsCart(size_t element)
{
    return productList[element];
}

size_t Cart::getSize() const noexcept
{
    return productList.size();
}

void Cart::Clear() noexcept
{
    if (productList.empty()) return;
    totalCount = 0;
    productList.clear();
    productList.shrink_to_fit();
    UIConsoleColor::printTextUseColor("🧹 Кошик очищено.\n", UIConsoleColor::Color::Yellow);
}

void Cart::ListCart() const noexcept
{
    if (productList.empty())
    {
        UIConsoleColor::printTextUseColor("⚠️  Кошик порожній.\n", UIConsoleColor::Color::Red);
        return;
    }

    UIConsoleColor::printTextUseColor("\n-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("                    ВМІСТ КОШИКА\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    for (const auto& product : productList)
    {
        product->GetInformationProduct();
    }

    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("Загальна сума: ", UIConsoleColor::Color::Green);
    std::cout << totalCount << " ₴\n";
}
