#include "TV.h"

TV::TV() : Product()
{
	resolution = " ";
}
TV::~TV()
{
}
void TV::GetInformationProduct() const noexcept
{
	Product::GetInformationProduct();
	std::cout << "Розмір: " << resolution << std::endl;
}
void TV::SetInformationProduct() noexcept
{
	Product::SetInformationProduct();
	std::cout << "Введіть розмір: ";
	std::cin.ignore();
	std::getline(std::cin, resolution);
}