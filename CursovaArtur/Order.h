#pragma once
#include "Product.h"
#include "Category.h"
#include "Customer.h"
#include "Payment.h"

class Cart;
class Order
{
public:
	Order(Cart& customerCarts, std::string& nameCustomer);
	double GetSum();
	void SetNewStatusOrder(int selection) noexcept;
	int getID() const noexcept;
private:

	static int Unic;
	int ID;
	double sum;
	std::string name;
	std::vector<std::shared_ptr<Product>> productPay;
	int status;
};
