#pragma once
#include <array>
#include "Category.h"
#include "Cart.h"

class Order;
class Customer
{
public:
	Cart customerCart;
	Customer(std::string& name, std::string& contactInformation, std::string& password);
	std::pair<int, std::shared_ptr<Order>> AddOrder(std::shared_ptr<Customer>& user);
	void getInformationCustomer() const noexcept;
	int DeleteOrder();
	int getID() const;
	std::string getName() noexcept;
	bool checkPassword();
	

private:
	static int Unic;
	int ID;
	std::string hash;
	std::string name;
	std::string contactInformation;
	bool admin;
	std::vector<int> myOrders;
};
