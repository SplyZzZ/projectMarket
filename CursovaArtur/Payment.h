#pragma once
#include <string>
#include "Product.h"
class Order;
class Payment
{
public:
	Payment();
	void InitializePayment(std::shared_ptr<Order>& order) noexcept;
	void approvePay(std::shared_ptr<Order>& order);
private:
	static int Unik;
	int ID;
	double sum;
	std::string paymentMethod;
	bool transactionStatus;
};