#include "ElectronicsStore.h"
#include "Factory.h"
#include "Security.h"

bool ElectronicsStore::addCustomer(std::string& name, std::string& contactInformation, std::string& password)
{
	if(customersTOid.find(name) != customersTOid.end()) return false;
	auto newUser = std::make_shared<Customer>(name, contactInformation, password);
	customersTOid[name] = newUser->getID();
	customers[newUser->getID()] = newUser;
	userSession = newUser;
	return true;
}
bool ElectronicsStore::deleteCustomer(int ID) noexcept
{
	return (customersTOid.erase(customers[ID]->getName())) && (customers.erase(ID));
}
bool ElectronicsStore::addCategory(std::string& name, std::string& description) noexcept
{
	auto tmp = std::make_shared<Category>(name, description);
	categories[tmp->getName()] = tmp; 
	return true; 
}
bool ElectronicsStore::deleteCategory(std::string& name) noexcept
{
	return categories.erase(name);
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
	PrintTypeProduct();
	std::cout << "Виберіть товар який бажаєте добавити: ";
	std::string selection = ConsoleHelper::readLine();
	auto iterator = productRegisty.find(selection);
	if (iterator == productRegisty.end()) { throw std::out_of_range("Не існує такого типу"); }
	auto& meta = iterator->second;
	std::shared_ptr<Product> newProduct = meta.FactoryMethod();
	newProduct->SetInformationProduct();
	if(!(StoreUtils::searchCategory(categories, meta.category)))
	{
		std::cout << "Введіть опис категорії: ";
		std::string description = ConsoleHelper::readLine();
		addCategory(meta.category, description);
	}
	categories[meta.category]->AddProduct(newProduct);
}
void ElectronicsStore::getCategoiesList() const noexcept
{
    if (categories.empty()) {
        std::cout << "Категорій немає.\n";
        return;
    }

	for (auto it = categories.begin(); it != categories.end(); ++it)
	{
		std::shared_ptr<Category> category = it->second;
		std::cout << category->getName() << " ";
	}
}
void ElectronicsStore::deleteProduct(std::string& name) noexcept
{
	categories[name]->GetListProduct();
	std::cout << "Введіть id товару який бажаєте видалити: ";
	int tmp = 0;
	std::cin >> tmp;
	categories[name]->DeleteProduct(tmp);
}
void ElectronicsStore::getProductList(std::string& name)  noexcept
{
	categories[name]->GetListProduct();
}
void ElectronicsStore::getClientsList() const noexcept
{
	if (customers.empty()) {
		std::cout << "Користувачів немає.\n";
		return;
	}

	for (auto it = customers.begin(); it != customers.end(); ++it)
	{
		std::shared_ptr<Customer> cust = it->second;
		cust->getInformationCustomer();
	}
}
std::shared_ptr<Customer> ElectronicsStore::getCustomer(int ID) noexcept
{
	return customers[ID];
}
bool ElectronicsStore::loginToStore(std::string& name, std::string& password)
{
	if(customersTOid.find(name) == customersTOid.end()) return false;
	if (customers[customersTOid[name]])
	{
		userSession = customers[customersTOid[name]];
		return true;
	}
	else
	{
		return false;
	}
	
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
	for (const auto& [key, meta] : productRegisty)
	{
		std::cout << key << " - " << meta.typeProduct << std::endl;
	}
}

                                                