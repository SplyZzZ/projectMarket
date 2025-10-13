#include "strategyPayment.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <string>
#include <iomanip>

namespace PaymentUI
{
    void printHeader(const std::string& title)
    {
        UIConsoleColor::printTextUseColor("\n=============================================================\n", UIConsoleColor::Color::Cyan);
        std::cout << "               " << title << "\n";
        UIConsoleColor::printTextUseColor("=============================================================\n", UIConsoleColor::Color::Cyan);
    }
}

void Card::payment()
{
    PaymentUI::printHeader("💳 Оплата карткою");
    UIConsoleColor::printTextUseColor("Тип оплати: ", UIConsoleColor::Color::Green);
    std::cout << "Банківська картка\n";

    UIConsoleColor::printTextUseColor("Стан операції: ", UIConsoleColor::Color::Green);
    std::cout << "✅ Успішно проведено\n";

    UIConsoleColor::printTextUseColor("Комісія: ", UIConsoleColor::Color::Green);
    std::cout << "1.5%\n";

    UIConsoleColor::printTextUseColor("Дякуємо за покупку!\n", UIConsoleColor::Color::Green);
}

void Crypt::payment()
{
    PaymentUI::printHeader("🪙 Оплата криптовалютою");
    UIConsoleColor::printTextUseColor("Тип оплати: ", UIConsoleColor::Color::Yellow);
    std::cout << "Криптовалюта (Bitcoin / ETH)\n";

    UIConsoleColor::printTextUseColor("Стан операції: ", UIConsoleColor::Color::Yellow);
    std::cout << "✅ Підтверджено мережею блокчейн\n";

    UIConsoleColor::printTextUseColor("Комісія: ", UIConsoleColor::Color::Yellow);
    std::cout << "0.0005 BTC\n";

    UIConsoleColor::printTextUseColor("Дякуємо за використання Web3!\n", UIConsoleColor::Color::Yellow);
}

void Certificate::payment()
{
    PaymentUI::printHeader("🎫 Оплата сертифікатом");
    UIConsoleColor::printTextUseColor("Тип оплати: ", UIConsoleColor::Color::Magenta);
    std::cout << "Подарунковий сертифікат\n";

    UIConsoleColor::printTextUseColor("Стан операції: ", UIConsoleColor::Color::Magenta);
    std::cout << "✅ Активовано\n";

    UIConsoleColor::printTextUseColor("Баланс сертифікату: ", UIConsoleColor::Color::Magenta);
    std::cout << "₴500 залишок\n";

    UIConsoleColor::printTextUseColor("Дякуємо, що обрали нас!\n", UIConsoleColor::Color::Magenta);
}

void Cash::payment()
{
    PaymentUI::printHeader("💵 Оплата готівкою");
    UIConsoleColor::printTextUseColor("Тип оплати: ", UIConsoleColor::Color::Green);
    std::cout << "Готівка\n";

    UIConsoleColor::printTextUseColor("Стан операції: ", UIConsoleColor::Color::Green);
    std::cout << "✅ Оплата прийнята\n";

    UIConsoleColor::printTextUseColor("Решта: ", UIConsoleColor::Color::Green);
    std::cout << "₴20\n";

    UIConsoleColor::printTextUseColor("Приємних покупок!\n", UIConsoleColor::Color::Green);
}
