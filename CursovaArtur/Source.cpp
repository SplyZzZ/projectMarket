#include <iostream>
#include "ElectronicsStore.h"
#include "argon2.h"
//#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
//void playMusic() 
//{
//    sf::Music music;
//    if (!music.openFromFile("background1.ogg")) 
//    {
//        std::cout << "Не вдалося завантажити музику!" << std::endl;
//        return;
//    }                        
//
//    music.setLooping(true);
//    music.play();
//
//    while (music.getStatus() == sf::SoundSource::Status::Playing) 
//    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//}
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
}

int main() {
    ElectronicsStore store;
  
    setlocale(LC_ALL, "UA");
    int choice;
    do {
        ShopUI::showMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
        {
            int tmp = 1;
            while (tmp != 0)
            {
                ShopUI::productsMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 1:
                {
                    if (store.getCategorySize() == 0)
                    {
                        std::cout << "Спершу створіть категорію!";
                        break;
                        tmp = 0;
                    }
                    else
                    {
                        std::string selection;
                        std::cout << "Введіть назву категорії в яку бажаєте добавити товар: ";
                        store.getCategoiesList();
                        std::cin >> selection;
                        store.addProducts(selection);
                    }
                    break;
                }
                case 2:
                {
                    if (store.getCategorySize() == 0)
                    {
                        std::cout << "Спершу створіть категорію!";
                        break;
                        tmp = 0;
                    }
                    else
                    {
                        std::string selection;
                        std::cout << "Введіть назву категорії в якій бажаєте видалити товар: ";
                        store.getCategoiesList();
                        std::cin >> selection;
                        store.deleteProduct(selection);
                    }
                    break;
                }
                case 3:
                {
                    if (store.getCategorySize() == 0)
                    {
                        std::cout << "Спершу створіть категорію!";
                        break;
                        tmp = 0;
                    }
                    else
                    {
                        std::string selection;
                        std::cout << "Введіть назву категорії в якій бажаєте переглянути список товарів: ";
                        store.getCategoiesList();
                        std::cin >> selection;
                        store.getProductList(selection);
                    }
                    break;
                }

                default:
                    std::cout << "Неправильний ввід\n";
                    tmp = 0;
                    break;
                }
            }
            break;
        }
        case 2:
        {
            int tmp = 1;
            while (tmp != 0)
            {
                ShopUI::categoriesMenu();
                std::cin >> tmp;
                switch (tmp)
                {
                case 1:
                {
                    std::string name, description;
                    std::cout << "Введіть ім'я категорії: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Введіть опис категорії: ";
                    std::getline(std::cin, description);
                    if (store.addCategory(name, description)) { std::cout << "Категорія успішно створена!"; }
                    else { std::cout << "Категорія з такою назвою вже існує!"; }
                    break;
                }
                case 2:
                {
                    std::string name;
                    std::cout << "Введіть ім'я категорії для видалення: ";
                    std::cin >> name;
                    if (store.deleteCategory(name)) { std::cout << "Категорія успішно видалена!"; }
                    else { std::cout << "Категорія з такою назвою не існує!"; }
                    break;
                }
                case 3:
                {
                    store.getCategoiesList();
                    break;
                }
                default:
                {
                    std::cout << "Не правильний ввід!!";
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
                case 1:
                {
                    std::string name, contactInformation, pass;
                    std::cout << "Введіть ім'я користувача: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Введіть пароль користувача: ";
                    std::getline(std::cin, pass);
                    std::cout << "Введіть контракту інформацію: ";
                    std::getline(std::cin, contactInformation);
                    std::cout << (store.addCustomer(name, contactInformation, pass)) ? "Користувача успішно додано! " : "Помилка! Користувач з таким ім'ям вже існує! ";
                    break;
                }
                case 2:
                {
                    int tmp;
                    std::cout << "Введіть ID користувача якого бажаєте видалити: ";
                    std::cin >> tmp;
                    std::cout << (store.deleteCustomer(tmp)) ?  "Користувач успішно видалений!"  :  "Помилка! Користувача з таким ID не існує"; ;
                    break;
                }
                case 3:
                {
                    store.getClientsList();
                    break;
                }
                default:
                {
                    std::cout << "Не правильний ввід!!";
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
                case 1:
                {
                  
                    std::cout << store.getUser()->customerCart.AddProduct(store.returnMapCategories()) ? "Товар успішно додано в корзину! " : "Помилка!";
                    break;
                }
                case 2:
                {
                   std::cout <<  (store.getUser()->customerCart.DeleteProduct()) ?  "Item successfully deleted" : "Shopping cart empty";
                   break;
                }
                case 3:
                {
                    store.getUser()->customerCart.ListCart();
                    break;
                }
                case 4:
                {
                   std::cout << store.getUser()->customerCart.ResulPrice() << " $";
                   break;
                }
                default:
                {
                    std::cout << "Не правильний ввід!!";
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
                case 1:
                {
                    std::shared_ptr<Customer> tempUser = store.getUser();
                    std::pair<int, std::shared_ptr<Order>> tempPairOrder = tempUser->AddOrder(tempUser);
                    store.addGlobalOrders(tempPairOrder);
                }
                case 2:
                {

                }
                }
                break;
            }
        }
        case 6:
        {
            ShopUI::reportsMenu();
            break;
        }
        case 7:
        {
            ShopUI::loyaltyMenu();
            break;
        }
        case 8:
        {
            ShopUI::recommendationMenu();
            break;
        }
        case 0:
        {
            std::cout << "Вихід з програми...\n";
            break;
        }
        default: std::cout << "Неправильний вибір. Спробуйте ще раз.\n"; break;
        }

    } while (choice != 0);

   
    return 0;
}
void ShopUI::showMainMenu() {
    std::cout << "================= Інтернет-магазин електроніки =================\n";
    std::cout << "1. Управління товарами\n";
    std::cout << "2. Управління категоріями\n";
    std::cout << "3. Управління клієнтами\n";
    std::cout << "4. Кошик покупок\n";
    std::cout << "5. Замовлення та оплати\n";
    std::cout << "6. Звіти\n";
    std::cout << "7. Програма лояльності\n";
    std::cout << "8. Система рекомендацій\n";
    std::cout << "0. Вихід\n";
    std::cout << "================================================================\n";
    std::cout << "Оберіть пункт меню: ";
}
void ShopUI::productsMenu() {
    std::cout << "\n--- Управління товарами ---\n";
    std::cout << "1. Додати товар\n";;
    std::cout << "2. Видалити товар\n";
    std::cout << "3. Переглянути список товарів\n";
    std::cout << "0. Назад\n";
}
void ShopUI::categoriesMenu() {
    std::cout << "\n--- Управління категоріями ---\n";
    std::cout << "1. Додати категорію\n";
    std::cout << "2. Видалити категорію\n";
    std::cout << "3. Переглянути категорії\n";
    std::cout << "0. Назад\n";
}
void ShopUI::customersMenu() {
    std::cout << "\n--- Управління клієнтами ---\n";
    std::cout << "1. Додати клієнта\n";
    std::cout << "2. Видалити клієнта\n";
    std::cout << "3. Переглянути профілі клієнтів\n";
    std::cout << "0. Назад\n";
}
void ShopUI::cartMenu() {
    std::cout << "\n--- Кошик покупок ---\n";
    std::cout << "1. Додати товар у кошик\n";
    std::cout << "2. Видалити товар з кошика\n";
    std::cout << "3. Переглянути кошик\n";
    std::cout << "4. Розрахувати загальну вартість\n";
    std::cout << "0. Назад\n";
}

void ShopUI::ordersMenu() {
    std::cout << "\n--- Замовлення та оплати ---\n";
    std::cout << "1. Створити замовлення\n";
    std::cout << "2. Провести оплату\n";
    std::cout << "3. Переглянути замовлення\n";
    std::cout << "0. Назад\n";
}

void ShopUI::reportsMenu() {
    std::cout << "\n--- Звіти ---\n";
    std::cout << "1. Звіт про продажі\n";
    std::cout << "2. Звіт про залишки на складі\n";
    std::cout << "0. Назад\n";
}

void ShopUI::loyaltyMenu() {
    std::cout << "\n--- Програма лояльності ---\n";
    std::cout << "1. Нарахувати бонусні бали\n";
    std::cout << "2. Використати бонусні бали\n";
    std::cout << "3. Перевірити баланс балів\n";
    std::cout << "0. Назад\n";
}

void ShopUI::recommendationMenu() {
    std::cout << "\n--- Система рекомендацій ---\n";
    std::cout << "1. Згенерувати рекомендації для клієнта\n";
    std::cout << "0. Назад\n";
}

void ShopUI::registerMenu()
{
    std::cout << "\n===== Авторизація =====\n";
    std::cout << "1. Реєстрація\n";
    std::cout << "2. Вхід\n";
    std::cout << "0. Вихід\n";
    std::cout << "Ваш вибір: ";
}
