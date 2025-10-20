#include "ElectronicsStore.h"
#include "Factory.h"
#include "Security.h"
#include "UIConsoleColor.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>



bool ElectronicsStore::addCustomer(std::string& name, std::string& contactInformation, std::string& password)
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "         ДОДАВАННЯ НОВОГО КЛІЄНТА\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (customersTOid.find(name) != customersTOid.end()) {
        UIConsoleColor::printTextUseColor("❌ Користувач з іменем \"" + name + "\" вже існує!\n", UIConsoleColor::Color::Red);
        return false;
    }

    auto newUser = std::make_shared<Customer>(name, contactInformation, password);
    customersTOid[name] = newUser->getID();
    customers[newUser->getID()] = newUser;
    userSession = newUser;

    UIConsoleColor::printTextUseColor("✅ Користувача \"" + name + "\" успішно додано до бази.\n", UIConsoleColor::Color::Green);
    return true;
}

bool ElectronicsStore::deleteCustomer(int ID) noexcept
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "          ВИДАЛЕННЯ КОРИСТУВАЧА\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (!customers.count(ID)) {
        UIConsoleColor::printTextUseColor("❌ Користувача з ID " + std::to_string(ID) + " не знайдено.\n", UIConsoleColor::Color::Red);
        return false;
    }

    std::string name = customers[ID]->getName();
    customersTOid.erase(name);
    customers.erase(ID);

    UIConsoleColor::printTextUseColor("✅ Користувача \"" + name + "\" успішно видалено.\n", UIConsoleColor::Color::Green);
    return true;
}

bool ElectronicsStore::addCategory(std::string& name, std::string& description) noexcept
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "          ДОДАВАННЯ КАТЕГОРІЇ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    auto tmp = std::make_shared<Category>(name, description);
    categories[tmp->getName()] = tmp;

    UIConsoleColor::printTextUseColor("✅ Категорію \"" + name + "\" додано до системи.\n", UIConsoleColor::Color::Green);
    return true;
}

bool ElectronicsStore::deleteCategory(std::string& name) noexcept
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "           ВИДАЛЕННЯ КАТЕГОРІЇ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (!(StoreUtils::searchCategory(categories, name)))
    {
        UIConsoleColor::printTextUseColor("❌ Категорію \"" + name + "\" не знайдено.\n", UIConsoleColor::Color::Red);
        return false;
    }

    categories.erase(name);
    UIConsoleColor::printTextUseColor("✅ Категорію \"" + name + "\" видалено.\n", UIConsoleColor::Color::Green);
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
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "          ДОДАВАННЯ ТОВАРУ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    PrintTypeProduct();
    UIConsoleColor::printTextUseColor("\nВиберіть тип товару для додавання: ", UIConsoleColor::Color::Yellow);
    std::string selection = ConsoleHelper::readLine();

    auto iterator = productRegisty.find(selection);
    if (iterator == productRegisty.end()) {
        UIConsoleColor::printTextUseColor("❌ Не існує такого типу продукту.\n", UIConsoleColor::Color::Red);
        throw std::out_of_range("Не існує такого типу");
    }

    auto& meta = iterator->second;
    std::shared_ptr<Product> newProduct = meta.FactoryMethod();
    newProduct->SetInformationProduct();

    if (!(StoreUtils::searchCategory(categories, meta.category)))
    {
        UIConsoleColor::printTextUseColor("Введіть опис нової категорії \"" + meta.category + "\": ", UIConsoleColor::Color::Yellow);
        std::string description = ConsoleHelper::readLine();
        addCategory(meta.category, description);
    }

    categories[meta.category]->AddProduct(newProduct);
    UIConsoleColor::printTextUseColor("✅ Товар успішно додано в категорію \"" + meta.category + "\".\n", UIConsoleColor::Color::Green);
}

void ElectronicsStore::getCategoiesList() const noexcept
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "               СПИСОК КАТЕГОРІЙ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (categories.empty()) {
        UIConsoleColor::printTextUseColor("⚠️  Категорій немає.\n", UIConsoleColor::Color::Red);
        return;
    }

    for (const auto& [name, category] : categories)
        UIConsoleColor::printTextUseColor("📦 " + name + "\n", UIConsoleColor::Color::Green);
}

void ElectronicsStore::deleteProduct(std::string& name) noexcept
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "           ВИДАЛЕННЯ ТОВАРУ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (categories.find(name) == categories.end()) {
        UIConsoleColor::printTextUseColor("❌ Категорію \"" + name + "\" не знайдено.\n", UIConsoleColor::Color::Red);
        return;
    }

    categories[name]->GetListProduct();
    UIConsoleColor::printTextUseColor("Введіть ID товару для видалення: ", UIConsoleColor::Color::Yellow);
    int tmp = 0;
    ConsoleHelper::readNumber(tmp);
    categories[name]->DeleteProduct(tmp);
    UIConsoleColor::printTextUseColor("✅ Товар з ID " + std::to_string(tmp) + " видалено.\n", UIConsoleColor::Color::Green);
}

void ElectronicsStore::getProductList(std::string& name) noexcept
{
    if (categories.find(name) == categories.end()) {
        UIConsoleColor::printTextUseColor("❌ Такої категорії не існує.\n", UIConsoleColor::Color::Red);
        return;
    }

    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "           ТОВАРИ КАТЕГОРІЇ: " + name + "\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    categories[name]->GetListProduct();
}

void ElectronicsStore::getClientsList() const noexcept
{
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "             СПИСОК КОРИСТУВАЧІВ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (customers.empty()) {
        UIConsoleColor::printTextUseColor("⚠️  Користувачів немає.\n", UIConsoleColor::Color::Red);
        return;
    }

    for (const auto& [id, cust] : customers)
    {
        UIConsoleColor::printTextUseColor("👤 ID: " + std::to_string(id) + "\n", UIConsoleColor::Color::Magenta);
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
    UIConsoleColor::printTextUseColor("\n---------------------------------------------\n"
        "             ВХІД ДО МАГАЗИНУ\n"
        "---------------------------------------------\n", UIConsoleColor::Color::Cyan);

    if (customersTOid.find(name) == customersTOid.end()) {
        UIConsoleColor::printTextUseColor("❌ Користувача \"" + name + "\" не знайдено.\n", UIConsoleColor::Color::Red);
        return false;
    }

    auto customer = customers[customersTOid[name]];
    if (customer && Security::verifyPassword(customer->getHash(), password)) {
        userSession = customer;
        UIConsoleColor::printTextUseColor("✅ Вхід виконано успішно! Вітаємо, " + name + "!\n", UIConsoleColor::Color::Green);
        return true;
    }

    UIConsoleColor::printTextUseColor("❌ Невірний пароль для користувача \"" + name + "\".\n", UIConsoleColor::Color::Red);
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
    UIConsoleColor::printTextUseColor("Доступні типи товарів:\n", UIConsoleColor::Color::Cyan);
    for (const auto& [key, meta] : productRegisty)
        UIConsoleColor::printTextUseColor("  " + key + " — " + meta.typeProduct + "\n", UIConsoleColor::Color::Yellow);
}

void ElectronicsStore::createReport()
{
    std::shared_ptr<BaseReport> report;

    UIConsoleColor::printTextUseColor("\nВиберіть тип звіту, який бажаєте створити:\n", UIConsoleColor::Color::Cyan);
    UIConsoleColor::printTextUseColor(" 1️⃣  Звіт по продуктах\n", UIConsoleColor::Color::Yellow);
    UIConsoleColor::printTextUseColor(" 2️⃣  Звіт по замовленнях\n", UIConsoleColor::Color::Yellow);
    UIConsoleColor::printTextUseColor(" 3️⃣  Звіт по клієнтах\n", UIConsoleColor::Color::Yellow);

    size_t selection = 0;
    ConsoleHelper::readNumber(selection);

    switch (selection)
    {
    case 1:
        report = std::make_shared<ProductReports>(categories);
        break;
    case 2:
        report = std::make_shared<OrderReports>(orders);
        break;
    case 3:
        report = std::make_shared<CustomersReports>(customers);
        break;
    default:
        UIConsoleColor::printTextUseColor("❌ Неправильний вибір.\n", UIConsoleColor::Color::Red);
        return;
    }

    report->GenerateReport();
}

