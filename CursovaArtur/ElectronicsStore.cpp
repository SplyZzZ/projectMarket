#include "ElectronicsStore.h"
#include "Factory.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace UIConsoleColor;

bool ElectronicsStore::addCustomer(std::string& name, std::string& contactInformation, std::string& password)
{
    printTextUseColor("\n---------------------------------------------\n"
        "         ДОДАВАННЯ НОВОГО КЛІЄНТА\n"
        "---------------------------------------------\n", Color::Cyan);

    if (customersTOid.find(name) != customersTOid.end()) {
        printTextUseColor("❌ Користувач з іменем \"" + name + "\" вже існує!\n", Color::Red);
        return false;
    }

    auto newUser = std::make_shared<Customer>(name, contactInformation, password);
    customersTOid[name] = newUser->getID();
    customers[newUser->getID()] = newUser;
    userSession = newUser;

    printTextUseColor("✅ Користувача \"" + name + "\" успішно додано до бази.\n", Color::Green);
    return true;
}

bool ElectronicsStore::deleteCustomer(int ID) noexcept
{
    printTextUseColor("\n---------------------------------------------\n"
        "          ВИДАЛЕННЯ КОРИСТУВАЧА\n"
        "---------------------------------------------\n", Color::Cyan);

    if (!customers.count(ID)) {
        printTextUseColor("❌ Користувача з ID " + std::to_string(ID) + " не знайдено.\n", Color::Red);
        return false;
    }

    std::string name = customers[ID]->getName();
    customersTOid.erase(name);
    customers.erase(ID);

    printTextUseColor("✅ Користувача \"" + name + "\" успішно видалено.\n", Color::Green);
    return true;
}

bool ElectronicsStore::addCategory(std::string& name, std::string& description) noexcept
{
    printTextUseColor("\n---------------------------------------------\n"
        "          ДОДАВАННЯ КАТЕГОРІЇ\n"
        "---------------------------------------------\n", Color::Cyan);

    auto tmp = std::make_shared<Category>(name, description);
    categories[tmp->getName()] = tmp;

    printTextUseColor("✅ Категорію \"" + name + "\" додано до системи.\n", Color::Green);
    return true;
}

bool ElectronicsStore::deleteCategory(std::string& name) noexcept
{
    printTextUseColor("\n---------------------------------------------\n"
        "           ВИДАЛЕННЯ КАТЕГОРІЇ\n"
        "---------------------------------------------\n", Color::Cyan);

    if (!(StoreUtils::searchCategory(categories, name)))
    {
        printTextUseColor("❌ Категорію \"" + name + "\" не знайдено.\n", Color::Red);
        return false;
    }

    categories.erase(name);
    printTextUseColor("✅ Категорію \"" + name + "\" видалено.\n", Color::Green);
    return true;
}

size_t ElectronicsStore::getCategorySize() const noexcept
{
    return categories.size();
}

size_t ElectronicsStore::getClientsSize() const noexcept
{
    return customers.size();
}

void ElectronicsStore::addProducts()
{
    printTextUseColor("\n---------------------------------------------\n"
        "          ДОДАВАННЯ ТОВАРУ\n"
        "---------------------------------------------\n", Color::Cyan);

    PrintTypeProduct();
    printTextUseColor("\nВиберіть тип товару для додавання: ", Color::Yellow);
    std::string selection = ConsoleHelper::readLine();

    auto iterator = productRegisty.find(selection);
    if (iterator == productRegisty.end()) {
        printTextUseColor("❌ Не існує такого типу продукту.\n", Color::Red);
        throw std::out_of_range("Не існує такого типу");
    }

    auto& meta = iterator->second;
    std::shared_ptr<Product> newProduct = meta.FactoryMethod();
    newProduct->SetInformationProduct();

    if (!(StoreUtils::searchCategory(categories, meta.category)))
    {
        printTextUseColor("Введіть опис нової категорії \"" + meta.category + "\": ", Color::Yellow);
        std::string description = ConsoleHelper::readLine();
        addCategory(meta.category, description);
    }

    categories[meta.category]->AddProduct(newProduct);
    printTextUseColor("✅ Товар успішно додано в категорію \"" + meta.category + "\".\n", Color::Green);
}

void ElectronicsStore::getCategoiesList() const noexcept
{
    printTextUseColor("\n---------------------------------------------\n"
        "               СПИСОК КАТЕГОРІЙ\n"
        "---------------------------------------------\n", Color::Cyan);

    if (categories.empty()) {
        printTextUseColor("⚠️  Категорій немає.\n", Color::Red);
        return;
    }

    for (const auto& [name, category] : categories)
        printTextUseColor("📦 " + name + "\n", Color::Green);
}

void ElectronicsStore::deleteProduct(std::string& name) noexcept
{
    printTextUseColor("\n---------------------------------------------\n"
        "           ВИДАЛЕННЯ ТОВАРУ\n"
        "---------------------------------------------\n", Color::Cyan);

    if (categories.find(name) == categories.end()) {
        printTextUseColor("❌ Категорію \"" + name + "\" не знайдено.\n", Color::Red);
        return;
    }

    categories[name]->GetListProduct();
    printTextUseColor("Введіть ID товару для видалення: ", Color::Yellow);
    int tmp = 0;
    ConsoleHelper::readNumber(tmp);
    categories[name]->DeleteProduct(tmp);
    printTextUseColor("✅ Товар з ID " + std::to_string(tmp) + " видалено.\n", Color::Green);
}

void ElectronicsStore::getProductList(std::string& name) noexcept
{
    if (categories.find(name) == categories.end()) {
        printTextUseColor("❌ Такої категорії не існує.\n", Color::Red);
        return;
    }

    printTextUseColor("\n---------------------------------------------\n"
        "           ТОВАРИ КАТЕГОРІЇ: " + name + "\n"
        "---------------------------------------------\n", Color::Cyan);

    categories[name]->GetListProduct();
}

void ElectronicsStore::getClientsList() const noexcept
{
    printTextUseColor("\n---------------------------------------------\n"
        "             СПИСОК КОРИСТУВАЧІВ\n"
        "---------------------------------------------\n", Color::Cyan);

    if (customers.empty()) {
        printTextUseColor("⚠️  Користувачів немає.\n", Color::Red);
        return;
    }

    for (const auto& [id, cust] : customers)
    {
        printTextUseColor("👤 ID: " + std::to_string(id) + "\n", Color::Magenta);
        cust->getInformationCustomer();
        std::cout << "---------------------------------------------\n";
    }
}

std::shared_ptr<Customer> ElectronicsStore::getCustomer(int ID) noexcept
{
    return customers[ID];
}

bool ElectronicsStore::loginToStore(std::string& name, std::string& password)
{
    printTextUseColor("\n---------------------------------------------\n"
        "             ВХІД ДО МАГАЗИНУ\n"
        "---------------------------------------------\n", Color::Cyan);

    if (customersTOid.find(name) == customersTOid.end()) {
        printTextUseColor("❌ Користувача \"" + name + "\" не знайдено.\n", Color::Red);
        return false;
    }

    auto customer = customers[customersTOid[name]];
    if (customer && Security::verifyPassword(customer->getHash(), password)) {
        userSession = customer;
        printTextUseColor("✅ Вхід виконано успішно! Вітаємо, " + name + "!\n", Color::Green);
        return true;
    }

    printTextUseColor("❌ Невірний пароль для користувача \"" + name + "\".\n", Color::Red);
    return false;
}

std::shared_ptr<Customer> ElectronicsStore::getUser() noexcept
{
    return userSession;
}

std::unordered_map<std::string, std::shared_ptr<Category>>& ElectronicsStore::returnMapCategories()
{
    return categories;
}

void ElectronicsStore::addGlobalOrders(std::pair<int, std::shared_ptr<Order>>& other)
{
    orders[other.first] = other.second;
}

void ElectronicsStore::PrintTypeProduct() const noexcept
{
    printTextUseColor("Доступні типи товарів:\n", Color::Cyan);
    for (const auto& [key, meta] : productRegisty)
        printTextUseColor("  " + key + " — " + meta.typeProduct + "\n", Color::Yellow);
}
