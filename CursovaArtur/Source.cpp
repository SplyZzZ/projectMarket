#include <iostream>
#include <thread>
#include <chrono>
#include "ElectronicsStore.h"
#include "argon2.h"
#include "Security.h"
#include <clocale>
#include <windows.h>
// ANSI кольори
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"

namespace ShopUI
{
    void showMainMenu();
    void productsMenu();
    void categoriesMenu();
    void customersMenu();
    void cartMenu();
    void ordersMenu();
    void reportsMenu();
    void loyaltyMenu();
    void recommendationMenu();
    void registerMenu();
    void printHeader(const std::string& title);
}

int main() {
    ElectronicsStore store;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::setlocale(LC_ALL, "uk_UA.UTF-8");
 
    int choice = 0;

    std::cout << CYAN;
    ShopUI::printHeader("ЛАСКАВО ПРОСИМО ДО ІНТЕРНЕТ-МАГАЗИНУ ЕЛЕКТРОНІКИ");
    std::cout << RESET;
    std::this_thread::sleep_for(std::chrono::milliseconds(600));

    do {
        ShopUI::showMainMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int tmp = 1;
            while (tmp != 0)
            {
                ShopUI::productsMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    store.addProducts();
                    break;
                }
                case 2:
                {
                    if (store.getCategorySize() == 0)
                        std::cout << RED << "⚠️  Спершу створіть категорію!\n" << RESET;
                    else {
                        std::string selection;
                        std::cout << YELLOW << "Введіть назву категорії для видалення товару: " << RESET;
                        store.getCategoiesList();
                        selection = ConsoleHelper::readLine();
                        store.deleteProduct(selection);
                    }
                    break;
                }
                case 3:
                {
                    if (store.getCategorySize() == 0)
                        std::cout << RED << "⚠️  Спершу створіть категорію!\n" << RESET;
                    else {
                        std::string selection;
                        std::cout << YELLOW << "Введіть назву категорії для перегляду: " << RESET;
                        store.getCategoiesList();
                        selection = ConsoleHelper::readLine();
                        store.getProductList(selection);
                    }
                    break;
                }
                default:
                {
                    std::cout << RED << "❌ Неправильний ввід.\n" << RESET;
                    tmp = 0;
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            int tmp = 1;
            while (tmp != 0) {
                ShopUI::categoriesMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    std::string name, description;
                    std::cout << YELLOW << "Введіть назву категорії: " << RESET;
                    name = ConsoleHelper::readLine();
                    std::cout << YELLOW << "Введіть опис категорії: " << RESET;
                    description = ConsoleHelper::readLine();
                    std::cout << (store.addCategory(name, description)
                        ? GREEN "✅ Категорію успішно створено!\n" RESET
                        : RED "❌ Категорія з такою назвою вже існує!\n" RESET);
                    break;
                }
                case 2:
                {
                    std::string name;
                    std::cout << YELLOW << "Введіть назву категорії для видалення: " << RESET;
                    name = ConsoleHelper::readLine();
                    std::cout << (store.deleteCategory(name)
                        ? GREEN "✅ Категорію успішно видалено!\n" RESET
                        : RED "❌ Категорії не знайдено!\n" RESET);
                    break;
                }
                case 3:
                {
                    store.getCategoiesList();
                    break;
                }
                default:
                {
                    std::cout << RED << "❌ Неправильний ввід.\n" << RESET;
                    tmp = 0;
                    break;

                }
                }
            }
            break;
        }

        case 3:
        {
            int tmp = 1;
            while (tmp != 0)
            {
                ShopUI::customersMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    std::string name, contactInformation, pass;
                    std::cout << YELLOW << "Введіть ім’я користувача: " << RESET;
                    name =  ConsoleHelper::readLine();
                    std::cout << YELLOW << "Введіть пароль: " << RESET;
                    pass = ConsoleHelper::readLine();
                    std::cout << YELLOW << "Введіть контактну інформацію: " << RESET;
                    contactInformation = ConsoleHelper::readLine();

                    std::cout << (store.addCustomer(name, contactInformation, pass)
                        ? GREEN "✅ Користувача додано!\n" RESET
                        : RED "❌ Ім’я вже використовується!\n" RESET);
                    break;
                }
                case 2:
                {
                    int tmpId;
                    std::cout << YELLOW << "Введіть ID користувача для видалення: " << RESET;
                    std::cin >> tmpId;
                    std::cout << (store.deleteCustomer(tmpId)
                        ? GREEN "✅ Користувача успішно видалено!\n" RESET
                        : RED "❌ Такого користувача не існує!\n" RESET);
                    break;
                }
                case 3:
                {
                    store.getClientsList();
                    break;
                }
                default:
                {
                    std::cout << RED << "❌ Неправильний ввід.\n" << RESET;
                    tmp = 0;
                    break;
                }
                }
            }
            break;
        }

        case 4:
        {
            int tmp = 1;
            while (tmp != 0)
            {
                ShopUI::cartMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    std::cout << (store.getUser()->customerCart.AddProduct(store.returnMapCategories())
                        ? GREEN "✅ Товар додано в кошик!\n" RESET
                        : RED "❌ Помилка при додаванні.\n" RESET);
                    break;
                }
                case 2:
                {
                    std::cout << (store.getUser()->customerCart.DeleteProduct()
                        ? GREEN "✅ Товар видалено з кошика!\n" RESET
                        : RED "⚠️  Кошик порожній.\n" RESET);
                    break;
                }
                case 3:
                {
                    store.getUser()->customerCart.ListCart();
                    break;
                }
                case 4:
                {
                    std::cout << CYAN << "Загальна вартість: " << store.getUser()->customerCart.ResulPrice() << " ₴\n" << RESET;
                    break;
                }
                default:
                {
                    std::cout << RED << "❌ Неправильний ввід.\n" << RESET;
                    tmp = 0;
                    break;
                }
                }
            }
            break;
        }

        case 5:
        {
            int tmp = 1;
            while (tmp != 0)
            {
                ShopUI::ordersMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    auto user = store.getUser();
                    auto orderPair = user->AddOrder(user);
                    store.addGlobalOrders(orderPair);
                    break;
                }
                case 2:
                {
                    size_t selection = 0;
                    store.getUser()->getUserOrderList();
                    std::cout << YELLOW << "Введіть ID замовлення: " << RESET;
                    std::cin >> selection;
                    auto orderUser = store.getUser()->getOrder(selection);
                    std::cout << (store.getUser()->getOrder(selection)->paymentOrder.InitializePayment(orderUser)
                        ? GREEN "✅ Оплату виконано успішно!\n" RESET
                        : RED "❌ Помилка оплати!\n" RESET);
                    break;
                }
                default:
                {
                    std::cout << RED << "❌ Неправильний ввід.\n" << RESET;
                    tmp = 0;
                    break;
                }
                }
            }
            break;
        }

        case 0:
            std::cout << GREEN << "\nДякуємо за використання програми! Вихід...\n" << RESET;
            break;

        default:
            std::cout << RED << "❌ Невірний вибір. Спробуйте ще раз.\n" << RESET;
            break;
        }

    } while (choice != 0);

    return 0;
}

// ---------------------------------------------
//              Графічний інтерфейс
// ---------------------------------------------
void ShopUI::printHeader(const std::string& title)
{
    std::cout << CYAN << "=============================================================\n";
    std::cout << "     " << title << "\n";
    std::cout << "=============================================================\n" << RESET;
}

void ShopUI::showMainMenu() {
    printHeader("ГОЛОВНЕ МЕНЮ");
    std::cout << "1. Управління товарами\n"
        << "2. Управління категоріями\n"
        << "3. Управління клієнтами\n"
        << "4. Кошик покупок\n"
        << "5. Замовлення та оплати\n"
        << "0. Вихід\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Оберіть пункт меню: " << RESET;
}

void ShopUI::productsMenu() {
    printHeader("УПРАВЛІННЯ ТОВАРАМИ");
    std::cout << "1. Додати товар\n"
        << "2. Видалити товар\n"
        << "3. Переглянути список товарів\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::categoriesMenu() {
    printHeader("УПРАВЛІННЯ КАТЕГОРІЯМИ");
    std::cout << "1. Додати категорію\n"
        << "2. Видалити категорію\n"
        << "3. Переглянути всі категорії\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::customersMenu() {
    printHeader("УПРАВЛІННЯ КЛІЄНТАМИ");
    std::cout << "1. Додати клієнта\n"
        << "2. Видалити клієнта\n"
        << "3. Переглянути клієнтів\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::cartMenu() {
    printHeader("КОШИК ПОКУПОК");
    std::cout << "1. Додати товар у кошик\n"
        << "2. Видалити товар з кошика\n"
        << "3. Переглянути вміст кошика\n"
        << "4. Розрахувати загальну вартість\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::ordersMenu() {
    printHeader("ЗАМОВЛЕННЯ ТА ОПЛАТИ");
    std::cout << "1. Створити замовлення\n"
        << "2. Провести оплату\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::reportsMenu() {
    printHeader("ЗВІТИ");
    std::cout << "1. Звіт про продажі\n"
        << "2. Звіт про залишки\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::loyaltyMenu() {
    printHeader("ПРОГРАМА ЛОЯЛЬНОСТІ");
    std::cout << "1. Нарахувати бонусні бали\n"
        << "2. Використати бонуси\n"
        << "3. Перевірити баланс\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::recommendationMenu() {
    printHeader("СИСТЕМА РЕКОМЕНДАЦІЙ");
    std::cout << "1. Згенерувати рекомендації для клієнта\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}

void ShopUI::registerMenu()
{
    printHeader("АВТОРИЗАЦІЯ");
    std::cout << "1. Реєстрація\n"
        << "2. Вхід\n"
        << "0. Вихід\n"
        << "-------------------------------------------------------------\n"
        << YELLOW << "Ваш вибір: " << RESET;
}
