#include "Payment.h"
#include "Order.h"
#include <thread>
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
Payment::Payment() : transactionStatus(false), sum(0), paymentMethod(nullptr)
{
	ID = ++Unik;

}
bool Payment::InitializePayment(std::shared_ptr<Order>& order) noexcept
{
    std::cout << CYAN
        << "\n==============================================\n"
        << "           СИСТЕМА ОБРОБКИ ПЛАТЕЖІВ\n"
        << "==============================================\n" << RESET;

    std::cout << "Номер операції: " << ID << "\n";
    std::cout << "Сума до сплати: ₴" << std::fixed << std::setprecision(2) << sum << "\n\n";

    std::cout << "Оберіть спосіб оплати:\n";
    std::cout << "  [1] 💳 Картка\n";
    std::cout << "  [2] 💵 Готівка\n";
    std::cout << "  [3] 🪙 Криптовалюта\n";
    std::cout << "  [4] 🎫 Сертифікат\n\n";

    std::cout << YELLOW << "Введіть номер варіанту: " << RESET;
    size_t selection = 0;
    std::cin >> selection;
    switch (selection)
    {
    case 1:
    {
        paymentMethod = std::make_unique<Card>();
        break;
    }
    case 2:
    {
        paymentMethod = std::make_unique<Cash>();
        break;
    }
    case 3: 
    {
        paymentMethod = std::make_unique<Crypt>();
        break;
    }
    case 4:
    {
        paymentMethod = std::make_unique<Crypt>();
        break;
    }
    default: 
    {
        std::cout << RED << "\n❌ Невірний вибір! Операцію скасовано.\n" << RESET;
        return false;
    }
    }
    return approvePay(order);

}

bool Payment::approvePay(std::shared_ptr<Order>& order)
{
    std::cout << CYAN
        << "\n----------------------------------------------\n"
        << "       ПІДТВЕРДЖЕННЯ ОПЛАТИ ЗАМОВЛЕННЯ\n"
        << "----------------------------------------------\n" << RESET;

    std::cout << "У вас є " << YELLOW << "5 хвилин" << RESET
        << " для підтвердження замовлення.\n\n"
        << "  [1] ✅ Підтвердити\n"
        << "  [2] ❌ Скасувати\n\n"
        << YELLOW << "Ваш вибір: " << RESET;

    std::size_t selection{};
    std::cin >> selection;

    if (selection == 2)
    {
        std::cout << RED << "\n❌ Замовлення скасовано користувачем.\n" << RESET;
        transactionStatus = false;
        return false;
    }

    if (selection != 1)
    {
        std::cout << RED << "\n⚠️  Невірний вибір! Операцію скасовано.\n" << RESET;
        transactionStatus = false;
        return false;
    }

    transactionStatus = true;

 
    std::cout << CYAN << "\nПідтвердження транзакції";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    std::cout << RESET << "\n";

   
    if (paymentMethod)
    {
        std::cout << GREEN << "\n✅ Оплату підтверджено!\n" << RESET;
        paymentMethod->payment();
    }
    else
    {
        std::cerr << RED << "\n❌ Помилка: метод оплати не ініціалізовано!\n" << RESET;
        throw std::runtime_error("Помилка в операції!");
    }

    order->SetNewStatusOrder(++selection);

    std::cout << CYAN
        << "\n----------------------------------------------\n"
        << "       ТРАНЗАКЦІЯ ЗАВЕРШЕНА УСПІШНО\n"
        << "----------------------------------------------\n" << RESET;

    return true;
}


int Payment::Unik = 0;