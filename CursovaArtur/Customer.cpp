#include "Customer.h"
#include "Order.h"
#include <array>
#include <unordered_map>
#include "Security.h"


Customer::Customer(std::string& name, std::string& contactInformation, std::string& password) : name(name), contactInformation(contactInformation)
{
	hash = Security::hashPassword(password);
	ID = ++Unic;
	admin = false;
}

std::pair<int, std::shared_ptr<Order>> Customer::AddOrder(std::array<Category, 10>& listCategory)
{
	customerCart.AddProduct(listCategory);
	 std::shared_ptr<Order> newOrder = std::make_shared<Order>(customerCart, name);
	 std::pair<int, std::shared_ptr<Order>> tmp(newOrder->getID(), newOrder);
	 myOrders.push_back(newOrder->getID());
	 return tmp;
}

void Customer::getInformationCustomer() const noexcept
{
	std::cout << "ID: " << ID << "\n";
	std::cout << "Name: " << name << "\n";
	std::cout << "Contact Information: " << contactInformation << "\n";
}

int Customer::DeleteOrder()
{
	if (myOrders.size() == 0) return 1;
	for (size_t i = 0; i < myOrders.size(); i++)
	{
		std::cout << myOrders[i] << " ";
	}
	std::cout << "Введіть ID ордера: ";
	int selection = 0;
	std::cin >> selection;
	return selection;
}

int Customer::getID() const
{
	return ID;
}
std::string Customer::getName() noexcept
{
	return name;
}

int Customer::Unic = 0;
