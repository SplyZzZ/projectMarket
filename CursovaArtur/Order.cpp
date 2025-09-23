#include "Order.h"
#include "Cart.h"
#include "Payment.h"
#include <array>

Order::Order(std::shared_ptr<Customer>& user)
{
	for (size_t i = 0; i < user->customerCart.getSize(); ++i)
	{
		productPay.push_back(user->customerCart.GetElementsCart(i));
	}
	name = user->getName();
	sum = user->customerCart.ResulPrice();
	ID = ++Unic;
	status = 1;
	
	user->customerCart.Clear();
}
double Order::GetSum()
{
	return sum;
}
void Order::SetNewStatusOrder(int selection) noexcept
{
	status = selection;
	/*std::cout << "1 - New\n2 - Payed\n3 - Send\n4 - Delivered\n";
	std::cin >> status;*/
}
int Order::getID() const noexcept
{
	return ID;
}
int Order::Unic = 0;