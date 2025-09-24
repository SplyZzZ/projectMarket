#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class Product
{
public:
	Product();
	virtual ~Product();
	virtual void getInformationProduct() const noexcept = 0;
	virtual void setInformationProduct() noexcept = 0;
	int getID() const noexcept;
	double getPrice() const noexcept;
	std::string getName() const noexcept;
	std::string getDescription() const noexcept;
protected:
	void setPrice(const double& price)noexcept;
	void setName(const std::string& name)noexcept;
	void setDescription(const std::string& description) noexcept;
	void setSize(const size_t size) noexcept;
private:
	int ID;
	static int Unical;
	double price;
	size_t size;
	std::string name;
	std::string description;
	
};
class Phone : public Product
{
public:
	Phone();
	
	virtual void getInformationProduct() const noexcept override;
	virtual void setInformationProduct() noexcept override;
};