#include "Product.h"

Product::Product() : price(0), size(0), name(" "), description(" ") 
{
	ID = ++Unical;
}
Product::~Product()
{
}
void Product::getInformationProduct() const noexcept
{
	std::cout << std::left;
	std::cout << std::setw(14) << "ID:" << ID << std::endl;
	std::cout << std::setw(14) << "Price:" << price << std::endl;
	std::cout << std::setw(14) << "Size:" << size << std::endl;
	std::cout << std::setw(14) << "Name:" << name << std::endl;
	std::cout << std::setw(14) << "Description:" << description << std::endl;
}
void Product::setInformationProduct() noexcept
{
	std::cout << "Enter Price: ";
std::cin >> price;
std::cout << "Enter Size: ";
std::cin >> size;
std::cout << "Enter Name: ";
std::cin.ignore();
std::getline(std::cin, name);
std::cout << "Description: ";
std::getline(std::cin, description);
}
int Product::getID() const noexcept
{
	return ID;
}
double Product::getPrice() const noexcept
{
	return price;
}
std::string Product::GetName() noexcept
{
	return name;
}
int Product::Unical = 0;

Phone::Phone() : Product()
{
	model = " ";
}
Phone::~Phone(){}
void Phone::getInformationProduct() const noexcept
{
	Product::getInformationProduct();
	std::cin.ignore();
	std::cout << "Модель: " << model << std::endl;
}
void Phone::setInformationProduct() noexcept
{
	Product::setInformationProduct();
	std::cout << "Введіть модель телефону: ";
	std::cin.ignore();
	std::getline(std::cin, model);
}

TV::TV() : Product()
{
	resolution = " ";
}
TV::~TV()
{
}
void TV::getInformationProduct() const noexcept
{
	Product::getInformationProduct();
	std::cout << "Розмір: " << resolution << std::endl;
}
void TV::setInformationProduct() noexcept
{
	Product::setInformationProduct();
	std::cout << "Введіть розмір: ";
	std::cin.ignore();
	std::getline(std::cin, resolution);
}

exercise::exercise() : Product()
{
	type = " ";
}
exercise::~exercise(){}
void exercise::getInformationProduct() const noexcept
{
	Product::getInformationProduct();
	std::cout << "Тип: " << type << std::endl;
}
void exercise::setInformationProduct() noexcept
{
	Product::setInformationProduct();
	std::cout << "Введіть тип зарядки: ";
	std::cin.ignore();
	std::getline(std::cin, type);
}

FleshDrive::FleshDrive() : Product()
{
	sizeGB = 0;
}
FleshDrive::~FleshDrive(){}
void FleshDrive::getInformationProduct() const noexcept
{
	Product::getInformationProduct();
	std::cout << "GB: " << sizeGB << std::endl;
}
void FleshDrive::setInformationProduct() noexcept
{
	Product::setInformationProduct();
	std::cout << "Введіть розмір флешки в гігабайтах: ";
	std::cin >> sizeGB;
}
