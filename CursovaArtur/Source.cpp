#include <iostream>
#include <thread>
#include <chrono>
#include "ElectronicsStore.h"
#include "argon2.h"
#include "Security.h"
#include <clocale>
#include <windows.h>
#include "UIConsoleColor.h"

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

int main() 
{
    ElectronicsStore store;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::setlocale(LC_ALL, "uk_UA.UTF-8");
 
    int choice = 0;

  
    ShopUI::printHeader("ЛАСКАВО ПРОСИМО ДО ІНТЕРНЕТ-МАГАЗИНУ ЕЛЕКТРОНІКИ");

    std::this_thread::sleep_for(std::chrono::milliseconds(600));

    do 
    {
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
                    UIConsoleColor::printTextUseColor("✅ Товар успішно створено!\n", UIConsoleColor::Color::Green);
                    break;
                }
                case 2:
                {
                    if (store.getCategorySize() == 0)
                    {
                        
                        UIConsoleColor::printTextUseColor("⚠️  Спершу створіть категорію!\n", UIConsoleColor::Color::Red);
                     
                    }
                    else 
                    {
                        std::string selection;
                        UIConsoleColor::printTextUseColor("Введіть назву категорії для видалення товару: ", UIConsoleColor::Color::Yellow);
                        store.getCategoiesList();
                        selection = ConsoleHelper::readLine();
                        store.deleteProduct(selection);
                    }
                    break;
                }
                case 3:
                {
                    if (store.getCategorySize() == 0)
                    {
                        UIConsoleColor::printTextUseColor("⚠️  Спершу створіть категорію!\n", UIConsoleColor::Color::Red);
                    }
                    else 
                    {
                        std::string selection;                    
                        UIConsoleColor::printTextUseColor("Введіть назву категорії для перегляду: ", UIConsoleColor::Color::Yellow);
                        store.getCategoiesList();
                        selection = ConsoleHelper::readLine();
                        store.getProductList(selection);
                    }
                    break;
                }
                default:
                {
                    UIConsoleColor::printTextUseColor("❌ Неправильний ввід.\n", UIConsoleColor::Color::Red);
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
                    UIConsoleColor::printTextUseColor("Введіть назву категорії: ", UIConsoleColor::Color::Yellow);
                    name = ConsoleHelper::readLine();
                    UIConsoleColor::printTextUseColor("Введіть опис категорії : ", UIConsoleColor::Color::Yellow);
                    description = ConsoleHelper::readLine();
                    if (store.addCategory(name, description))
                    {
                        UIConsoleColor::printTextUseColor("✅ Категорію успішно створено!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("❌ Категорія з такою назвою вже існує!\n", UIConsoleColor::Color::Red);
                    }
                        
                    break;
                }
                case 2:
                {
                    std::string name;
                    UIConsoleColor::printTextUseColor("Введіть назву категорії для видалення: ", UIConsoleColor::Color::Yellow);
                    name = ConsoleHelper::readLine();
                    if (store.deleteCategory(name))
                    {
                        UIConsoleColor::printTextUseColor("✅ Категорію успішно видалено!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("❌ Категорії не знайдено!\n", UIConsoleColor::Color::Red);
                    }
                    break;
                }
                case 3:
                {
                    store.getCategoiesList();
                    break;
                }
                default:
                {
                    UIConsoleColor::printTextUseColor("❌ Неправильний ввід.\n", UIConsoleColor::Color::Red);
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
                    UIConsoleColor::printTextUseColor("Введіть ім’я користувача: ", UIConsoleColor::Color::Yellow);
                    name =  ConsoleHelper::readLine();
                    UIConsoleColor::printTextUseColor("Введіть пароль: ", UIConsoleColor::Color::Yellow);
                    pass = ConsoleHelper::readLine();
                    UIConsoleColor::printTextUseColor("Введіть контактну інформацію: ", UIConsoleColor::Color::Yellow);
                    contactInformation = ConsoleHelper::readLine();

                    if (store.addCustomer(name, contactInformation, pass))
                    {
                        UIConsoleColor::printTextUseColor("✅ Користувача додано!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("❌ Ім’я вже використовується!\n", UIConsoleColor::Color::Red);
                    }
                    break;
                }
                case 2:
                {
                    int tmpId;
                    UIConsoleColor::printTextUseColor("Введіть ID користувача для видалення: ", UIConsoleColor::Color::Yellow);
                    std::cin >> tmpId;
                    if (store.deleteCustomer(tmpId))
                    {
                        UIConsoleColor::printTextUseColor("✅ Користувача успішно видалено!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("❌ Такого користувача не існує!\n", UIConsoleColor::Color::Red);
                    }
                    break;
                }
                case 3:
                {
                    store.getClientsList();
                    break;
                }
                default:
                {
                    UIConsoleColor::printTextUseColor("❌ Неправильний ввід.\n", UIConsoleColor::Color::Red);
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
                    std::cout << store.getUser()->getName();
                    if (store.getUser()->customerCart.AddProduct(store.returnMapCategories()))
                    {
                        UIConsoleColor::printTextUseColor("✅ Товар додано в кошик!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("❌ Помилка при додаванні.\n", UIConsoleColor::Color::Red);
                    }
                    break;
                }
                case 2:
                {
                    if (store.getUser()->customerCart.DeleteProduct())
                    {
                        UIConsoleColor::printTextUseColor("✅ Товар видалено з кошика!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("⚠️  Кошик порожній.\n", UIConsoleColor::Color::Red);
                    }
                    break;
                }
                case 3:
                {
                    store.getUser()->customerCart.ListCart();
                    break;
                }
                case 4:
                {
                    
                    UIConsoleColor::printTextUseColor("Загальна вартість: ", UIConsoleColor::Color::Cyan);

                    auto tmpSum = store.getUser()->customerCart.ResulPrice();
                    std::string Sum = std::to_string(tmpSum);

                    UIConsoleColor::printTextUseColor(Sum, UIConsoleColor::Color::Cyan);
                    UIConsoleColor::printTextUseColor(" ₴\n", UIConsoleColor::Color::Cyan);
               
                    break;
                }
                default:
                {
                    UIConsoleColor::printTextUseColor("❌ Неправильний ввід.\n", UIConsoleColor::Color::Red);
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
                    UIConsoleColor::printTextUseColor("Введіть ID замовлення: ",UIConsoleColor::Color::Yellow);
                    ConsoleHelper::readNumber(selection);
                    auto orderUser = store.getUser()->getOrder(selection);
                    if (store.getUser()->getOrder(selection)->paymentOrder.InitializePayment(orderUser))
                    {
                        UIConsoleColor::printTextUseColor("✅ Оплату виконано успішно!\n", UIConsoleColor::Color::Green);
                    }
                    else
                    {
                        UIConsoleColor::printTextUseColor("❌ Помилка оплати!\n", UIConsoleColor::Color::Red);
                    }
                    break;
                }
                default:
                {
                    UIConsoleColor::printTextUseColor("❌ Неправильний ввід.\n", UIConsoleColor::Color::Red);
                    tmp = 0;
                    break;
                }
                }
            }
            break;
        }

        case 0:
            UIConsoleColor::printTextUseColor("\nДякуємо за використання програми! Вихід...\n", UIConsoleColor::Color::Green);
            break;

        default:
            UIConsoleColor::printTextUseColor("❌ Невірний вибір. Спробуйте ще раз.\n", UIConsoleColor::Color::Red);
            break;
        }

    } while (choice != 0);

    return 0;
}


void ShopUI::printHeader(const std::string& title)
{
    UIConsoleColor::printTextUseColor("=============================================================\n", UIConsoleColor::Color::Cyan);
    std::cout << "     " << title << "\n";
    std::cout << "=============================================================\n";
}

void ShopUI::showMainMenu() {
    printHeader("ГОЛОВНЕ МЕНЮ");
    std::cout << "1. Управління товарами\n"
        << "2. Управління категоріями\n"
        << "3. Управління клієнтами\n"
        << "4. Кошик покупок\n"
        << "5. Замовлення та оплати\n"
        << "0. Вихід\n"
        << "-------------------------------------------------------------\n";
        UIConsoleColor::printTextUseColor("Оберіть пункт меню: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::productsMenu() {
    printHeader("УПРАВЛІННЯ ТОВАРАМИ");
    std::cout << "1. Додати товар\n"
        << "2. Видалити товар\n"
        << "3. Переглянути список товарів\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::categoriesMenu() {
    printHeader("УПРАВЛІННЯ КАТЕГОРІЯМИ");
    std::cout << "1. Додати категорію\n"
        << "2. Видалити категорію\n"
        << "3. Переглянути всі категорії\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::customersMenu() {
    printHeader("УПРАВЛІННЯ КЛІЄНТАМИ");
    std::cout << "1. Додати клієнта\n"
        << "2. Видалити клієнта\n"
        << "3. Переглянути клієнтів\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::cartMenu() {
    printHeader("КОШИК ПОКУПОК");
    std::cout << "1. Додати товар у кошик\n"
        << "2. Видалити товар з кошика\n"
        << "3. Переглянути вміст кошика\n"
        << "4. Розрахувати загальну вартість\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::ordersMenu() {
    printHeader("ЗАМОВЛЕННЯ ТА ОПЛАТИ");
    std::cout << "1. Створити замовлення\n"
        << "2. Провести оплату\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::reportsMenu() {
    printHeader("ЗВІТИ");
    std::cout << "1. Звіт про продажі\n"
        << "2. Звіт про залишки\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::loyaltyMenu() {
    printHeader("ПРОГРАМА ЛОЯЛЬНОСТІ");
    std::cout << "1. Нарахувати бонусні бали\n"
        << "2. Використати бонуси\n"
        << "3. Перевірити баланс\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::recommendationMenu() {
    printHeader("СИСТЕМА РЕКОМЕНДАЦІЙ");
    std::cout << "1. Згенерувати рекомендації для клієнта\n"
        << "0. Назад\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}

void ShopUI::registerMenu()
{
    printHeader("АВТОРИЗАЦІЯ");
    std::cout << "1. Реєстрація\n"
        << "2. Вхід\n"
        << "0. Вихід\n"
        << "-------------------------------------------------------------\n";
    UIConsoleColor::printTextUseColor("Ваш вибір: ", UIConsoleColor::Color::Yellow);
}
