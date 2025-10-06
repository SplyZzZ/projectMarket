#pragma once
#include <array>
#include "Category.h"
#include "Cart.h"
#include "Observer.h"
class Order;
class Customer : public IObserver
{
public:
	Cart customerCart;
	Customer(std::string& name, std::string& contactInformation, std::string& password);
	std::pair<int, std::shared_ptr<Order>> AddOrder(std::shared_ptr<Customer>& user);
	void getInformationCustomer() const noexcept;
	void getUserOrderList() const noexcept;
	int DeleteOrder();
	std::shared_ptr<Order> getOrder(size_t ID) noexcept;
	int getID() const;
	std::string getName() noexcept;
	void UpDate(size_t status, int ID) override;
private:
	static int Unic;
	int ID;
	std::string hash;
	std::string name;
	std::string contactInformation;
	bool admin;
	std::unordered_map<int, std::shared_ptr<Order>> myOrders;
};
