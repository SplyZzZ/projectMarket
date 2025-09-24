#include "Product.h"

Product::Product() : price(0), size(0), name(" "), description(" ") 
{
	ID = ++Unical;
}

Product::~Product()
{
}

int Product::getID() const noexcept
{
	return ID;
}
double Product::getPrice() const noexcept
{
	return price;
}
int Product::Unical = 0;

Phone::Phone() {}

void Phone::getInformationProduct() const noexcept
{
}

void Phone::setInformationProduct() noexcept
{
	double price;
	size_t size;
	std::string name;
	std::string description;
std::cout << "Enter Price: ";
std::cin >> price;
setPrice(price);
std::cout << "Enter Size: ";
std::cin >> size;
setSize(size);
std::cout << "Enter Name: ";
std::cin.ignore();
std::getline(std::cin, name);
setName(name);
std::cout << "Description: ";
std::getline(std::cin, description);
setDescription(description);
}
//std::cout << "Enter Price: ";
//std::cin >> price;
//std::cout << "Enter Size: ";
//std::cin >> size;
//std::cout << "Enter Name: ";
//std::cin.ignore();
//std::getline(std::cin, name);
//std::cout << "Description: ";
//std::getline(std::cin, description);
//std::cout << std::left;
//std::cout << std::setw(14) << "ID:" << ID << std::endl;
//std::cout << std::setw(14) << "Price:" << price << std::endl;
//std::cout << std::setw(14) << "Size:" << size << std::endl;
//std::cout << std::setw(14) << "Name:" << name << std::endl;
//std::cout << std::setw(14) << "Description:" << description << std::endl;