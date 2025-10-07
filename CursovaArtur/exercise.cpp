#include "exercise.h"
#include "Security.h"
Exercise::Exercise() : Product()
{type = " ";}
Exercise::~Exercise(){}
void Exercise::GetInformationProduct() const noexcept
{
	Product::GetInformationProduct();
	std::cout << "Тип: " << type << std::endl;
}
void Exercise::SetInformationProduct() noexcept
{
	Product::SetInformationProduct();
	std::cout << "Введіть тип зарядки: ";
	type = ConsoleHelper::readLine();
}
