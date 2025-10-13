#include "Order.h"
#include "Cart.h"
#include "Payment.h"
#include "UIConsoleColor.h"
#include <array>
#include <iostream>

Order::Order(std::shared_ptr<Customer>& user)
{
    for (size_t i = 0; i < user->customerCart.getSize(); ++i)
    {
        productPay.push_back(user->customerCart.GetElementsCart(i));
    }

    name = user->getName();
    sum = user->customerCart.ResulPrice();
    ID = ++Unic;
    status = 1;
    observer = user;
    user->customerCart.Clear();
}

double Order::GetSum()
{
    return sum;
}

void Order::SetNewStatusOrder(size_t selection) noexcept
{
    status = selection;
    Notify();
}

int Order::getID() const noexcept
{
    return ID;
}

void Order::GetOrderInformation() const noexcept
{
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("ІНФОРМАЦІЯ ПРО ЗАМОВЛЕННЯ\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    UIConsoleColor::printTextUseColor("ID замовлення: ", UIConsoleColor::Color::Cyan);
    std::cout << ID << "\n";

    UIConsoleColor::printTextUseColor("Ім’я замовника: ", UIConsoleColor::Color::Cyan);
    std::cout << name << "\n";

    UIConsoleColor::printTextUseColor("Сума замовлення: ", UIConsoleColor::Color::Cyan);
    std::cout << sum << " ₴\n";

    UIConsoleColor::printTextUseColor("Статус замовлення: ", UIConsoleColor::Color::Cyan);

    switch (status)
    {
    case 1:
        UIConsoleColor::printTextUseColor("🆕 Нове\n", UIConsoleColor::Color::Yellow);
        break;
    case 2:
        UIConsoleColor::printTextUseColor("💰 Оплачене\n", UIConsoleColor::Color::Green);
        break;
    case 3:
        UIConsoleColor::printTextUseColor("📦 Відправлене\n", UIConsoleColor::Color::Blue);
        break;
    case 4:
        UIConsoleColor::printTextUseColor("✅ Доставлене\n", UIConsoleColor::Color::Magenta);
        break;
    default:
        UIConsoleColor::printTextUseColor("❓ Невідомий статус\n", UIConsoleColor::Color::Red);
        break;
    }

    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("Перелік товарів:\n", UIConsoleColor::Color::Yellow);

    if (productPay.empty())
    {
        UIConsoleColor::printTextUseColor("⚠️  У цьому замовленні немає товарів.\n", UIConsoleColor::Color::Red);
    }
    else
    {
        for (size_t i = 0; i < productPay.size(); ++i)
        {
            productPay[i]->GetInformationProduct();
        }
    }

    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
}

void Order::Notify()
{
    if (auto user = observer.lock())
    {
        user->UpDate(status, ID);
    }
}

int Order::Unic = 0;
