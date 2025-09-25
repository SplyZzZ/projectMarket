#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
class Product
{
public:
	Product();
	virtual ~Product();
	virtual void GetInformationProduct() const noexcept;
	virtual void SetInformationProduct() noexcept;
	int GetID() const noexcept;
	double GetPrice() const noexcept;
	std::string GetName() noexcept;
private:
	int ID;
	static int Unical;
	double price;
	size_t size;
	std::string name;
	std::string description;
};

