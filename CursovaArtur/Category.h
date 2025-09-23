#pragma once
#include "Product.h"
#include <unordered_map>

class Category
{
public:
	Category(std::string& name, std::string& description);
	void AddProduct(std::shared_ptr<Product>& other) noexcept;
	void DeleteProduct(const int ID) noexcept;
	void GetListProduct() const noexcept;
	std::shared_ptr<Product> GetProduct(int ID)  noexcept;
	std::string getName() const noexcept;
private:
	int ID;
	std::string name;
	static int Unik;
	std::string description;
	std::unordered_map<int, std::shared_ptr<Product>> productMap;
};
