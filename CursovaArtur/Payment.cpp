#include "Payment.h"
#include "Order.h"
#include "UIConsoleColor.h"
#include <thread>
#include <iomanip>
#include <iostream>

Payment::Payment() : transactionStatus(false), sum(0), paymentMethod(nullptr)
{
    ID = ++Unik;
}

bool Payment::InitializePayment(std::shared_ptr<Order>& order) noexcept
{
    UIConsoleColor::printTextUseColor("\n=============================================================\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("             СИСТЕМА ОБРОБКИ ПЛАТЕЖІВ\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("=============================================================\n", UIConsoleColor::Color::Cyan);

    UIConsoleColor::printTextUseColor("Номер операції: ", UIConsoleColor::Color::Cyan);
    std::cout << ID << "\n";

    UIConsoleColor::printTextUseColor("Сума до сплати: ", UIConsoleColor::Color::Cyan);
    std::cout << "₴" << std::fixed << std::setprecision(2) << order->GetSum() << "\n\n";

    UIConsoleColor::printTextUseColor("Оберіть спосіб оплати:\n", UIConsoleColor::Color::Yellow);
    std::cout << "  [1] 💳 Картка\n"
        << "  [2] 💵 Готівка\n"
        << "  [3] 🪙 Криптовалюта\n"
        << "  [4] 🎫 Сертифікат\n\n";

    UIConsoleColor::printTextUseColor("Введіть номер варіанту: ", UIConsoleColor::Color::Yellow);
    size_t selection = 0;
    std::cin >> selection;

    switch (selection)
    {
    case 1:
        paymentMethod = std::make_unique<Card>();
        break;
    case 2:
        paymentMethod = std::make_unique<Cash>();
        break;
    case 3:
        paymentMethod = std::make_unique<Crypt>();
        break;
    case 4:
        paymentMethod = std::make_unique<Certificate>();
        break;
    default:
        UIConsoleColor::printTextUseColor("\n❌ Невірний вибір! Операцію скасовано.\n", UIConsoleColor::Color::Red);
        return false;
    }

    sum = order->GetSum();
    return approvePay(order);
}

bool Payment::approvePay(std::shared_ptr<Order>& order)
{
    UIConsoleColor::printTextUseColor("\n-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("         ПІДТВЕРДЖЕННЯ ОПЛАТИ ЗАМОВЛЕННЯ\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    std::cout << "У вас є ";
    UIConsoleColor::printTextUseColor("5 хвилин", UIConsoleColor::Color::Yellow);
    std::cout << " для підтвердження замовлення.\n\n";

    std::cout << "  [1] ✅ Підтвердити\n"
        << "  [2] ❌ Скасувати\n\n";

    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
    std::size_t selection{};
    std::cin >> selection;

    if (selection == 2)
    {
        UIConsoleColor::printTextUseColor("\n❌ Замовлення скасовано користувачем.\n", UIConsoleColor::Color::Red);
        transactionStatus = false;
        return false;
    }

    if (selection != 1)
    {
        UIConsoleColor::printTextUseColor("\n⚠️  Невірний вибір! Операцію скасовано.\n", UIConsoleColor::Color::Red);
        transactionStatus = false;
        return false;
    }

    transactionStatus = true;

    UIConsoleColor::printTextUseColor("\nПідтвердження транзакції", UIConsoleColor::Color::Cyan);
    for (int i = 0; i < 3; ++i)
    {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    std::cout << "\n";

    if (paymentMethod)
    {
        UIConsoleColor::printTextUseColor("\n✅ Оплату підтверджено!\n", UIConsoleColor::Color::Green);
        paymentMethod->payment();
    }
    else
    {
        UIConsoleColor::printTextUseColor("\n❌ Помилка: метод оплати не ініціалізовано!\n", UIConsoleColor::Color::Red);
        throw std::runtime_error("Помилка в операції!");
    }

    order->SetNewStatusOrder(2); 

    UIConsoleColor::printTextUseColor("\n-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("          ТРАНЗАКЦІЯ ЗАВЕРШЕНА УСПІШНО\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("-------------------------------------------------------------\n", UIConsoleColor::Color::Cyan);

    return true;
}

int Payment::Unik = 0;
