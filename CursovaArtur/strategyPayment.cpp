#include "strategyPayment.h"
#include <iostream>
#include <string>
#include <iomanip>
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
void printHeader(const std::string& title)
{
    std::cout << CYAN << "\n========================================\n";
    std::cout << "         " << title << "\n";
    std::cout << "========================================" << RESET << "\n";
}

void Card::payment()
{
    printHeader("💳 Оплата карткою");
    std::cout << GREEN << std::left << std::setw(20) << "Тип оплати:" << "Банківська картка\n";
    std::cout << std::setw(20) << "Стан операції:" << "✅ Успішно проведено\n";
    std::cout << std::setw(20) << "Комісія:" << "1.5%\n";
    std::cout << std::setw(20) << "Дякуємо за покупку!" << RESET << "\n";
}

void Crypt::payment()
{
    printHeader("🪙 Оплата криптовалютою");
    std::cout << YELLOW << std::left << std::setw(20) << "Тип оплати:" << "Криптовалюта (Bitcoin / ETH)\n";
    std::cout << std::setw(20) << "Стан операції:" << "✅ Підтверджено мережею блокчейн\n";
    std::cout << std::setw(20) << "Комісія:" << "0.0005 BTC\n";
    std::cout << std::setw(20) << "Дякуємо за використання Web3!" << RESET << "\n";
}

void Certificate::payment()
{
        printHeader("🎫 Оплата сертифікатом");
        std::cout << MAGENTA << std::left << std::setw(20) << "Тип оплати:" << "Подарунковий сертифікат\n";
        std::cout << std::setw(20) << "Стан операції:" << "✅ Активовано\n";
        std::cout << std::setw(20) << "Баланс сертифікату:" << "₴500 залишок\n";
        std::cout << std::setw(20) << "Дякуємо, що обрали нас!" << RESET << "\n";
}

void Cash::payment()
{
    printHeader("💵 Оплата готівкою");
    std::cout << GREEN << std::left << std::setw(20) << "Тип оплати:" << "Готівка\n";
    std::cout << std::setw(20) << "Стан операції:" << "✅ Оплата прийнята\n";
    std::cout << std::setw(20) << "Решта:" << "₴20\n";
    std::cout << std::setw(20) << "Приємних покупок!" << RESET << "\n";
}
