#pragma once
#include <string>
#include "Order.h"
class Payment
{
public:
	Payment();
	void InitializePayment(std::shared_ptr<Order> order) noexcept;
	void approvePay(std::shared_ptr<Order> order);
private:
	static int Unik;
	int ID;
	double sum;
	std::string paymentMethod;
	int transactionStatus;
};