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
	for (const auto& [id, order] : myOrders) {
		std::cout << "ID: " << id << " ";
	}
	std::cout << "\nВведіть ID ордера: ";
	int selection = 0;
	ConsoleHelper::readNumber(selection);
	return selection;
}

std::shared_ptr<Order> Customer::getOrder(size_t ID) 
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

std::string Customer::getHash() const noexcept
{
	return hash;
}

void Customer::UpDate(size_t status, int ID)
{
	std::cout << "Статус вашого замволення " << getOrder(ID) << " змінено на " << ((status == 1) ? "New" : (status == 2) ? "Payed" : (status == 3) ? "Send" : "Delivered")
		<< "\n";
}



int Customer::Unic = 0;
