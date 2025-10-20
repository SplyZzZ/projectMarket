#include "Payment.h"
#include "Order.h"
#include "UIConsoleColor.h"
#include <thread>
#include <iomanip>
#include "Customer.h"
#include <iostream>
#include "Security.h"

Payment::Payment() : transactionStatus(false), sum(0), paymentMethod(nullptr)
{
    ID = ++Unik;
}

bool Payment::InitializePayment(std::shared_ptr<Order>& order, std::shared_ptr<Customer>& user) noexcept
{
    UIConsoleColor::printTextUseColor("\n=============================================================\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("             СИСТЕМА ОБРОБКИ ПЛАТЕЖІВ\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor("=============================================================\n", UIConsoleColor::Color::Cyan);

    UIConsoleColor::printTextUseColor("Номер операції: ", UIConsoleColor::Color::Cyan);
    std::cout << ID << "\n";

    UIConsoleColor::printTextUseColor("Сума до сплати: ", UIConsoleColor::Color::Cyan);\
    sum = order->GetSum();
    std::cout << "₴" << std::fixed << std::setprecision(2) << sum << "\n\n";


    UIConsoleColor::printTextUseColor("Бажаєте викорситати бонусні бали?\n1 - Так\n2- Ні\n", UIConsoleColor::Color::Green);
    size_t options = 0;
    options = ConsoleHelper::readNumber(options);
    if (options == 1)
    {
        int selection = 1;
        while (selection == 1)
        {
            UIConsoleColor::printTextUseColor("Ваша кількість бонусних балів: ", UIConsoleColor::Color::Yellow);
            size_t countUserPoints = user->bonusPoints.getPurchaseCount();
            UIConsoleColor::printTextUseColor(std::to_string(countUserPoints), UIConsoleColor::Color::Yellow);
            size_t tmp = 0;
            UIConsoleColor::printTextUseColor("\nВведіть кількість бонусних балів які бажаєте потратити: ", UIConsoleColor::Color::Yellow);
            tmp = ConsoleHelper::readNumber(tmp);
            if (user->bonusPoints.removePurchase(tmp))
            {
                sum -= tmp;
                 UIConsoleColor::printTextUseColor("\nСума до сплати: ", UIConsoleColor::Color::Cyan);
                 std::cout << "₴" << std::fixed << std::setprecision(2) << sum << "\n\n";
            }
            else
            {
                UIConsoleColor::printTextUseColor("\nВи ввели не правильну кількість балів.\n", UIConsoleColor::Color::Red);
                UIConsoleColor::printTextUseColor("Ви бажаєте повторити спробу?\n1 - Так\n2 - Ні\n", UIConsoleColor::Color::Yellow);
                selection = ConsoleHelper::readNumber(selection);
                
            }
        }
    }

    UIConsoleColor::printTextUseColor("Оберіть спосіб оплати:\n", UIConsoleColor::Color::Yellow);
    std::cout << "  [1] 💳 Картка\n"
        << "  [2] 💵 Готівка\n"
        << "  [3] 🪙 Криптовалюта\n"
        << "  [4] 🎫 Сертифікат\n\n";

    UIConsoleColor::printTextUseColor("Введіть номер варіанту: ", UIConsoleColor::Color::Yellow);
    size_t selection = 0;
    selection = ConsoleHelper::readNumber(selection);

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
    return approvePay(order, user);
}

bool Payment::approvePay(std::shared_ptr<Order>& order, std::shared_ptr<Customer>& user)
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
        user->bonusPoints.addPurchase(order->GetSum() / 10);
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
