#pragma once
#include "Product.h"
#include "Category.h"
#include "Customer.h"
#include "Payment.h"
#include "Observer.h"
class Cart;

class Order : public ISubject
{
public:
	Order(std::shared_ptr<Customer>& user);
	double GetSum();
	void SetNewStatusOrder(size_t selection) noexcept;
	int getID() const noexcept;
	void GetOrderInformation() const noexcept;
	Payment paymentOrder;
	void Notify() override;
private:

	static int Unic;
	int ID;
	std::weak_ptr<IObserver> observer;
	double sum;
	std::string name;
	std::vector<std::shared_ptr<Product>> productPay;
	int status;
};
