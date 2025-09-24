#include "ElectronicsStore.h"

bool ElectronicsStore::addCustomer(std::string& name, std::string& contactInformation, std::string& password)
{
	if(customersTOid.find(name) != customersTOid.end()) return false;
	std::shared_ptr<Customer> newUser = std::make_shared<Customer>(name, contactInformation, password);
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
	std::shared_ptr<Category> tmp = std::make_shared<Category>(name, description);
	if (categories.find(tmp->getName()) == categories.end()) { categories[tmp->getName()] = tmp; return true; }
	return false;	
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
void ElectronicsStore::addProducts(std::string& name) noexcept
{
	std::shared_ptr<Product> tmp = std::make_shared<Product>();
	tmp->setInformationProduct();	
	categories[name]->AddProduct(tmp);
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
		category->getName();
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
                                                