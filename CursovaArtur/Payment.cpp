#include "Payment.h"

#include "Order.h"
Payment::Payment() : transactionStatus(false), sum(0), paymentMethod(" ")
{
	ID = ++Unik;

}
bool Payment::InitializePayment(std::shared_ptr<Order>& order) noexcept
{
	ID = ++Unik;
	sum = order->GetSum();
	std::cout << "Enter your payment method: ";
	std::cin.ignore();
	std::getline(std::cin, paymentMethod);
	return approvePay(order);
}

bool Payment::approvePay(std::shared_ptr<Order>& order)
{
	std::cout << "You have 5 minutes to confirm your order \n1 - confirm\n2 - cancel ";
	int selection;
	std::cin >> selection;
	if (selection == 2) return false;
	transactionStatus = true;
	order->SetNewStatusOrder(++selection);
	return true;
}


int Payment::Unik = 0;