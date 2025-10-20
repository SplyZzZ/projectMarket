#pragma once
#include <string>
#include "Product.h"
#include "strategyPayment.h"
class Order;
class Customer;
class Payment
{
public:
	Payment();
	bool InitializePayment(std::shared_ptr<Order>& order, std::shared_ptr<Customer>& user) noexcept;
	bool approvePay(std::shared_ptr<Order>& order, std::shared_ptr<Customer>& user);
private:
	static int Unik;
	int ID;
	double sum;
	std::unique_ptr<IStrategy> paymentMethod;
	bool transactionStatus;
};