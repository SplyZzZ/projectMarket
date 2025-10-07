#include "Product.h"
#include "FleshDrive.h"
#include "Security.h"
Product::Product() : price(0), size(0), name(" "), description(" ") 
{
	ID = ++Unical;
}
Product::~Product()
{
}
void Product::GetInformationProduct() const noexcept
{
	std::cout << std::left;
	std::cout << std::setw(14) << "ID:" << ID << std::endl;
	std::cout << std::setw(14) << "Price:" << price << std::endl;
	std::cout << std::setw(14) << "Size:" << size << std::endl;
	std::cout << std::setw(14) << "Name:" << name << std::endl;
	std::cout << std::setw(14) << "Description:" << description << std::endl;
}
void Product::SetInformationProduct() noexcept
{
	std::cout << "Enter Price: ";
	ConsoleHelper::readNumber(price);
	std::cout << "Enter Size: ";
	ConsoleHelper::readNumber(size);
	std::cout << "Enter Name: ";
	ConsoleHelper::readLine();
	std::cout << "Description: ";
	ConsoleHelper::readLine();
}
int Product::GetID() const noexcept
{
	return ID;
}
double Product::GetPrice() const noexcept
{
	return price;
}
std::string Product::GetName() const noexcept
{
	return name;
}

int Product::Unical = 0;


