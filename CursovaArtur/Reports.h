#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>
#include "ElectronicsStore.h"
#include "UIConsoleColor.h"

class BaseReport
{
public:
    virtual ~BaseReport() = default;

  
    void GenerateReport()
    {
        PrintHeader();
        PrintBody();
        PrintFooter();
    }

protected:
    virtual void PrintHeader() = 0;
    virtual void PrintBody() = 0;
    virtual void PrintFooter() = 0;
};


class ProductReports : public BaseReport
{
private:
    const std::unordered_map<std::string, std::shared_ptr<Category>>& categories;

public:
    ProductReports(const std::unordered_map<std::string, std::shared_ptr<Category>>& cats)
        : categories(cats) {
    }

protected:
    void PrintHeader() override
    {
        UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
            "             ЗВІТ ПО ПРОДУКТАХ\n"
            "---------------------------------------------\n", UIConsoleColor::Color::Cyan);
    }

    void PrintBody() override
    {
        if (categories.empty()) {
            UIConsoleColor::printTextUseColor("⚠️  Немає жодної категорії.\n", UIConsoleColor::Color::Red);
            return;
        }

        for (const auto& [catName, category] : categories)
        {
            UIConsoleColor::printTextUseColor("\n📦 Категорія: " + catName + "\n", UIConsoleColor::Color::Green);
            const auto& products = category->returnProductMap();

            if (products.empty()) {
                UIConsoleColor::printTextUseColor("  ⚠️  У цій категорії немає товарів.\n", UIConsoleColor::Color::Red);
                continue;
            }

            for (const auto& [id, product] : products)
            {
                std::cout << "  🏷️ Назва: " << product->GetName()
                    << " | Залишок: " << product->GetSize() << "\n";
            }
        }
    }

    void PrintFooter() override
    {
        UIConsoleColor::printTextUseColor("\n✅ Звіт по продуктах завершено.\n", UIConsoleColor::Color::Green);
    }
};


class OrderReports : public BaseReport
{
private:
    std::unordered_map<int, std::shared_ptr<Order>>& orders;

public:
    OrderReports(std::unordered_map<int, std::shared_ptr<Order>>& ord)
        : orders(ord) {
    }

protected:
    void PrintHeader() override
    {
        UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
            "             ЗВІТ ПО ЗАМОВЛЕННЯХ\n"
            "---------------------------------------------\n", UIConsoleColor::Color::Cyan);
    }

    void PrintBody() override
    {
        if (orders.empty()) 
        {
            UIConsoleColor::printTextUseColor("⚠️  Немає жодного замовлення.\n", UIConsoleColor::Color::Red);
            return;
        }

        size_t totalSum = 0;
        for (const auto& [id, order] : orders)
        {
            UIConsoleColor::printTextUseColor("🧾 Замовлення ID: " + std::to_string(id) + "\n", UIConsoleColor::Color::Magenta);
            order->GetOrderInformation();
            totalSum += order->GetSum();
            std::cout << "---------------------------------------------\n";
        }
        UIConsoleColor::printTextUseColor("💰 Загальна сума замовлень: " + std::to_string(totalSum) + "\n", UIConsoleColor::Color::Yellow);
    }

    void PrintFooter() override
    {
        UIConsoleColor::printTextUseColor("✅ Звіт по замовленнях завершено.\n", UIConsoleColor::Color::Green);
    }
};


class CustomersReports : public BaseReport
{
private:
    std::unordered_map<int, std::shared_ptr<Customer>>& customers;

public:
    CustomersReports(std::unordered_map<int, std::shared_ptr<Customer>>& cust)
        : customers(cust) {
    }

protected:
    void PrintHeader() override
    {
        UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
            "             ЗВІТ ПО КЛІЄНТАМ\n"
            "---------------------------------------------\n", UIConsoleColor::Color::Cyan);
    }

    void PrintBody() override
    {
        if (customers.empty()) {
            printTextUseColor("⚠️  Немає жодного клієнта.\n", UIConsoleColor::Color::Red);
            return;
        }

        size_t totalClients = 0;
        for (const auto& [id, customer] : customers)
        {
            UIConsoleColor::printTextUseColor("👤 Клієнт ID: " + std::to_string(id) + "\n", UIConsoleColor::Color::Magenta);
            customer->getInformationCustomer();
            std::cout << "---------------------------------------------\n";
            totalClients++;
        }
        UIConsoleColor::printTextUseColor("👥 Загальна кількість клієнтів: " + std::to_string(totalClients) + "\n", UIConsoleColor::Color::Yellow);
    }

    void PrintFooter() override
    {
        UIConsoleColor::printTextUseColor("✅ Звіт по клієнтах завершено.\n", UIConsoleColor::Color::Green);
    }
};
