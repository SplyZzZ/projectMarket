#pragma once
#include <iostream>
#include <iomanip>
#include <string>
enum class ProductType {
	Phone,
	TV,
	Exercise,
	FleshDrive
};
class Product
{
public:
	Product();
	virtual ~Product();
	virtual void getInformationProduct() const noexcept;
	virtual void setInformationProduct() noexcept;
	int getID() const noexcept;
	double getPrice() const noexcept;
	std::string GetName() noexcept;
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
	~Phone();
	virtual void getInformationProduct() const noexcept override;
	virtual void setInformationProduct() noexcept override;
private:
	std::string model;
};
class TV : public Product
{
public:
	TV();
	~TV();
	virtual void getInformationProduct() const noexcept override;
	virtual void setInformationProduct() noexcept override;
private:
	std::string resolution;
};
class exercise : public Product
{
public:
	exercise();
	~exercise();
	virtual void getInformationProduct() const noexcept override;
	virtual void setInformationProduct() noexcept override;
private:
	std::string type;
};
class FleshDrive : public Product
{
public:
	FleshDrive();
	~FleshDrive();
	virtual void getInformationProduct() const noexcept override;
	virtual void setInformationProduct() noexcept override;
private:
	size_t sizeGB;
}; 
class FactoryMethod
{
public:
	static std::shared_ptr<Product> initiProductNew(ProductType type)
	{
		switch (type)
		{
		case ProductType::Phone:
		{
			return std::make_shared<Phone>();
			break;
		}
		case ProductType::TV:
		{
			return std::make_shared<TV>();
			break;
		}
		case ProductType::Exercise:
		{
			return std::make_shared<exercise>();
			break;
		}
		case ProductType::FleshDrive:
		{
			return std::make_shared<FleshDrive>();
			break;
		}
		default:
		{
			throw std::invalid_argument("Unknown ProductType");
			break;
		}
		}
	}
};