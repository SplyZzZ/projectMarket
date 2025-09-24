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

std::pair<int, std::shared_ptr<Order>> Customer::AddOrder(std::shared_ptr<Customer>& user)
{
	 std::shared_ptr<Order> newOrder = std::make_shared<Order>(user);
	 std::pair<int, std::shared_ptr<Order>> tmp(newOrder->getID(), newOrder);
	 myOrders[newOrder->getID()] = newOrder;
	 return tmp;
}

void Customer::getInformationCustomer() const noexcept
{
	std::cout << "ID: " << ID << "\n";
	std::cout << "Name: " << name << "\n";
	std::cout << "Contact Information: " << contactInformation << "\n";
}

void Customer::getUserOrderList() const noexcept
{
	for (auto it = myOrders.begin(); it != myOrders.end(); ++it) {
		if (it->second) {
			it->second->GetOrderInformation();
		}
	}
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

std::shared_ptr<Order> Customer::getOrder(size_t ID) noexcept
{
	if(myOrders.find(ID) == myOrders.end()) throw std::out_of_range("Некоректний індекс масиву");
	return myOrders[ID];
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
