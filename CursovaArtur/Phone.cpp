#include "Phone.h"

Phone::Phone() : Product()
{
	model = " ";
}
Phone::~Phone(){}
void Phone::GetInformationProduct() const noexcept
{
	Product::GetInformationProduct();
	std::cin.ignore();
	std::cout << "Модель: " << model << std::endl;
}
void Phone::SetInformationProduct() noexcept
{
	Product::SetInformationProduct();
	std::cout << "Введіть модель телефону: ";
	std::cin.ignore();
	std::getline(std::cin, model);
}