#include "Order.h"
#include "Cart.h"
#include <array>

Order::Order(Cart& customerCarts, std::string& nameCustomer)
{
	for (size_t i = 0; i < customerCarts.getSize(); i++)
	{
		productPay.push_back(customerCarts.GetElementsCart(i));
	}
	name = nameCustomer;
	sum = customerCarts.ResulPrice();
	ID = ++Unic;
	status = 1;
	customerCarts.Clear();
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