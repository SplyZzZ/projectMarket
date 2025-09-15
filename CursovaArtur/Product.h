#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class Product
{
public:
	Product();
	void getInformationProduct() const noexcept;
	void setInformationProduct() noexcept;
	int getID() const noexcept;
	double getPrice() const noexcept;
private:
	int ID;
	static int Unical;
	double price;
	size_t size;
	std::string name;
	std::string description;
};
