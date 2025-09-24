#pragma once
#include <string>
#include "Product.h"
class Order;
class Payment
{
public:
	Payment();
	bool InitializePayment(std::shared_ptr<Order>& order) noexcept;
	bool approvePay(std::shared_ptr<Order>& order);
private:
	static int Unik;
	int ID;
	double sum;
	std::string paymentMethod;
	bool transactionStatus;
};