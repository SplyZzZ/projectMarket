#pragma once
#include "Category.h"
#include "Customer.h"
#include "Order.h"
#include "Observer.h"
#include "Reports.h"
class ElectronicsStore
{
public:
	bool addCustomer(std::string& name, std::string& contactInformation, std::string& password);
	bool deleteCustomer(int ID) noexcept;
	bool addCategory(std::string& name, std::string& description) noexcept;
	bool deleteCategory(std::string& name) noexcept;
	size_t getCategorySize() const noexcept;
	size_t getClientsSize() const noexcept;
	void addProducts();
	void getCategoiesList() const noexcept;
	void deleteProduct(std::string& name) noexcept;
	void getProductList(std::string& name)  noexcept;
	void getClientsList() const noexcept;
	std::shared_ptr<Customer> getCustomer(int ID) noexcept;
	bool loginToStore(std::string& name, std::string& password);
	std::shared_ptr<Customer> getUser() noexcept;
    std::unordered_map<std::string, std::shared_ptr<Category>>& returnMapCategories();
	void addGlobalOrders(std::pair<int, std::shared_ptr<Order>>& other);
	void PrintTypeProduct() const noexcept;
	void createReport();
private:
	std::unordered_map<int, std::shared_ptr<Customer>> customers;
	std::unordered_map <std::string, int> customersTOid;
	std::unordered_map<int, std::shared_ptr<Order>> orders;
	std::unordered_map<std::string, std::shared_ptr<Category>> categories;
	std::shared_ptr<Customer> userSession = std::make_shared<Customer>("Jumaice", "arraaa");
}; 