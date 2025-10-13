#include "Customer.h"
#include "Order.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <array>
#include <unordered_map>
#include <iostream>

Customer::Customer(std::string&& name, std::string&& contactInformation)
    : name(name), contactInformation(contactInformation)
{
    ID = ++Unic;
    admin = false;
    hash = "0";
}

Customer::Customer(std::string& name, std::string& contactInformation, std::string& password)
    : name(name), contactInformation(contactInformation)
{
    hash = Security::hashPassword(password);
    ID = ++Unic;
    admin = false;
}

std::pair<int, std::shared_ptr<Order>> Customer::AddOrder(std::shared_ptr<Customer>& user)
{
    std::shared_ptr<Order> newOrder = std::make_shared<Order>(user);
    std::pair<int, std::shared_ptr<Order>> tmp(newOrder->getID(), newOrder);
    myOrders[newOrder->getID()] = newOrder;
    return tmp;
}

void Customer::getInformationCustomer() const noexcept
{
    UIConsoleColor::printTextUseColor("ID: ", UIConsoleColor::Color::Cyan);
    std::cout << ID << "\n";

    UIConsoleColor::printTextUseColor("Ім’я: ", UIConsoleColor::Color::Cyan);
    std::cout << name << "\n";

    UIConsoleColor::printTextUseColor("Контактна інформація: ", UIConsoleColor::Color::Cyan);
    std::cout << contactInformation << "\n";
}

void Customer::getUserOrderList() const noexcept
{
    if (myOrders.empty()) {
        UIConsoleColor::printTextUseColor("⚠️  У вас немає жодного замовлення.\n", UIConsoleColor::Color::Red);
        return;
    }

    for (const auto& [id, order] : myOrders) {
        if (order) {
            order->GetOrderInformation();
        }
    }
}

int Customer::DeleteOrder()
{
    if (myOrders.empty()) {
        UIConsoleColor::printTextUseColor("⚠️  Немає замовлень для видалення.\n", UIConsoleColor::Color::Red);
        return 1;
    }

    UIConsoleColor::printTextUseColor("Доступні ID замовлень: ", UIConsoleColor::Color::Yellow);
    for (const auto& [id, order] : myOrders) {
        std::cout << id << " ";
    }

    std::cout << "\n";
    UIConsoleColor::printTextUseColor("Введіть ID ордера: ", UIConsoleColor::Color::Yellow);
    int selection = 0;
    ConsoleHelper::readNumber(selection);
    return selection;
}

std::shared_ptr<Order> Customer::getOrder(size_t ID)
{
    if (myOrders.find(ID) == myOrders.end())
        throw std::out_of_range("Некоректний індекс замовлення.");
    return myOrders[ID];
}

int Customer::getID() const
{
    return ID;
}

std::string Customer::getName() noexcept
{
    return name;
}

std::string Customer::getHash() const noexcept
{
    return hash;
}

void Customer::UpDate(size_t status, int ID)
{
    std::string statusText;
    switch (status)
    {
    case 1: statusText = "🆕 Нове"; break;
    case 2: statusText = "💰 Оплачене"; break;
    case 3: statusText = "📦 Відправлене"; break;
    case 4: statusText = "✅ Доставлене"; break;
    default: statusText = "❓ Невідомий статус"; break;
    }

    UIConsoleColor::printTextUseColor("Статус вашого замовлення ", UIConsoleColor::Color::Cyan);
    std::cout << getOrder(ID)->getID() << " змінено на ";
    UIConsoleColor::printTextUseColor(statusText + "\n", UIConsoleColor::Color::Green);
}

int Customer::Unic = 0;
