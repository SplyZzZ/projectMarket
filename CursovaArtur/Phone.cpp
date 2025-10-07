#include "Phone.h"
#include "Security.h"
Phone::Phone() : Product()
{
	model = " ";
}
Phone::~Phone(){}
void Phone::GetInformationProduct() const noexcept
{
	Product::GetInformationProduct();
	std::cout << "Модель: " << model << std::endl;
}
void Phone::SetInformationProduct() noexcept
{
	Product::SetInformationProduct();
	std::cout << "Введіть модель телефону: ";
	model = ConsoleHelper::readLine();
}