#include "ElectronicsStore.h"
#include "Factory.h"
#include "Security.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// Кольори ANSI
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"

bool ElectronicsStore::addCustomer(std::string& name, std::string& contactInformation, std::string& password)
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "         ДОДАВАННЯ НОВОГО КЛІЄНТА\n"
        << "---------------------------------------------\n" << RESET;

    if (customersTOid.find(name) != customersTOid.end()) {
        std::cout << RED << "❌ Користувач з іменем \"" << name << "\" вже існує!\n" << RESET;
        return false;
    }

    auto newUser = std::make_shared<Customer>(name, contactInformation, password);
    customersTOid[name] = newUser->getID();
    customers[newUser->getID()] = newUser;
    userSession = newUser;

    std::cout << GREEN << "✅ Користувача \"" << name << "\" успішно додано до бази.\n" << RESET;
    return true;
}

bool ElectronicsStore::deleteCustomer(int ID) noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "          ВИДАЛЕННЯ КОРИСТУВАЧА\n"
        << "---------------------------------------------\n" << RESET;

    if (!customers.count(ID)) {
        std::cout << RED << "❌ Користувача з ID " << ID << " не знайдено.\n" << RESET;
        return false;
    }

    std::string name = customers[ID]->getName();
    customersTOid.erase(name);
    customers.erase(ID);

    std::cout << GREEN << "✅ Користувача \"" << name << "\" успішно видалено.\n" << RESET;
    return true;
}

bool ElectronicsStore::addCategory(std::string& name, std::string& description) noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "          ДОДАВАННЯ КАТЕГОРІЇ\n"
        << "---------------------------------------------\n" << RESET;

    auto tmp = std::make_shared<Category>(name, description);
    categories[tmp->getName()] = tmp;

    std::cout << GREEN << "✅ Категорію \"" << name << "\" додано до системи.\n" << RESET;
    return true;
}

bool ElectronicsStore::deleteCategory(std::string& name) noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "           ВИДАЛЕННЯ КАТЕГОРІЇ\n"
        << "---------------------------------------------\n" << RESET;

    if (!(StoreUtils::searchCategory(categories, name))) 
    {
        std::cout << RED << "❌ Категорію \"" << name << "\" не знайдено.\n" << RESET;
        return false;
    }

    categories.erase(name);
    std::cout << GREEN << "✅ Категорію \"" << name << "\" видалено.\n" << RESET;
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

void ElectronicsStore::addProducts() noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "          ДОДАВАННЯ ТОВАРУ\n"
        << "---------------------------------------------\n" << RESET;

    PrintTypeProduct();
    std::cout << YELLOW << "\nВиберіть тип товару для додавання: " << RESET;
    std::string selection = ConsoleHelper::readLine();

    auto iterator = productRegisty.find(selection);
    if (iterator == productRegisty.end()) {
        std::cout << RED << "❌ Не існує такого типу продукту.\n" << RESET;
        throw std::out_of_range("Не існує такого типу");
    }

    auto& meta = iterator->second;
    std::shared_ptr<Product> newProduct = meta.FactoryMethod();
    newProduct->SetInformationProduct();

    if (!(StoreUtils::searchCategory(categories, meta.category)))
    {
        std::cout << YELLOW << "Введіть опис нової категорії \"" << meta.category << "\": " << RESET;
        std::string description = ConsoleHelper::readLine();
        addCategory(meta.category, description);
    }

    categories[meta.category]->AddProduct(newProduct);
    std::cout << GREEN << "✅ Товар успішно додано в категорію \"" << meta.category << "\".\n" << RESET;
}

void ElectronicsStore::getCategoiesList() const noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "               СПИСОК КАТЕГОРІЙ\n"
        << "---------------------------------------------\n" << RESET;

    if (categories.empty()) {
        std::cout << RED << "⚠️  Категорій немає.\n" << RESET;
        return;
    }

    for (const auto& [name, category] : categories)
    {
        std::cout << GREEN << "📦 " << name << RESET << std::endl;
    }
}

void ElectronicsStore::deleteProduct(std::string& name) noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "           ВИДАЛЕННЯ ТОВАРУ\n"
        << "---------------------------------------------\n" << RESET;

    if (categories.find(name) == categories.end()) {
        std::cout << RED << "❌ Категорію \"" << name << "\" не знайдено.\n" << RESET;
        return;
    }

    categories[name]->GetListProduct();
    std::cout << YELLOW << "Введіть ID товару для видалення: " << RESET;
    int tmp = 0;
    ConsoleHelper::readNumber(tmp);
    categories[name]->DeleteProduct(tmp);
    std::cout << GREEN << "✅ Товар з ID " << tmp << " видалено.\n" << RESET;
}

void ElectronicsStore::getProductList(std::string& name) noexcept
{
    if (categories.find(name) == categories.end()) {
        std::cout << RED << "❌ Такої категорії не існує.\n" << RESET;
        return;
    }

    std::cout << CYAN << "\n---------------------------------------------\n"
        << "           ТОВАРИ КАТЕГОРІЇ: " << name << "\n"
        << "---------------------------------------------\n" << RESET;

    categories[name]->GetListProduct();
}

void ElectronicsStore::getClientsList() const noexcept
{
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "             СПИСОК КОРИСТУВАЧІВ\n"
        << "---------------------------------------------\n" << RESET;

    if (customers.empty()) {
        std::cout << RED << "⚠️  Користувачів немає.\n" << RESET;
        return;
    }

    for (const auto& [id, cust] : customers)
    {
        std::cout << MAGENTA << "👤 ID: " << id << RESET << std::endl;
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
    std::cout << CYAN << "\n---------------------------------------------\n"
        << "             ВХІД ДО МАГАЗИНУ\n"
        << "---------------------------------------------\n" << RESET;

    if (customersTOid.find(name) == customersTOid.end()) {
        std::cout << RED << "❌ Користувача \"" << name << "\" не знайдено.\n" << RESET;
        return false;
    }

    auto customer = customers[customersTOid[name]];
    if (customer && Security::verifyPassword(customer->getHash(), password)) {
        userSession = customer;
        std::cout << GREEN << "✅ Вхід виконано успішно! Вітаємо, " << name << "!\n" << RESET;
        return true;
    }

    std::cout << RED << "❌ Невірний пароль для користувача \"" << name << "\".\n" << RESET;
    return false;
}

std::shared_ptr<Customer> ElectronicsStore::getUser() noexcept
{
    return userSession;
}

const std::unordered_map<std::string, std::shared_ptr<Category>>& ElectronicsStore::returnMapCategories()
{
    return categories;
}

void ElectronicsStore::addGlobalOrders(std::pair<int, std::shared_ptr<Order>>& other)
{
    orders[other.first] = other.second;
}

void ElectronicsStore::PrintTypeProduct() const noexcept
{
    std::cout << CYAN << "Доступні типи товарів:\n" << RESET;
    for (const auto& [key, meta] : productRegisty)
    {
        std::cout << "  " << YELLOW << key << RESET
            << " — " << meta.typeProduct << "\n";
    }
}
