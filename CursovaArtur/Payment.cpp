#include "Payment.h"

Payment::Payment() {}
void Payment::InitializePayment(std::shared_ptr<Order> order) noexcept
{
	ID = ++Unik;
	sum = order->GetSum();
	std::cout << "Enter your payment method: ";
	std::cin.ignore();
	std::getline(std::cin, paymentMethod);
	transactionStatus = 1;
	approvePay(order);
}

void Payment::approvePay(std::shared_ptr<Order> order)
{
	std::cout << "You have 5 minutes to confirm your order \n1 - confirm\n2 - cancel ";
	int selection;
	std::cin >> selection;
	if (selection == 1) order->SetNewStatusOrder(++selection);

}


int Payment::Unik = 0;