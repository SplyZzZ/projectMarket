#pragma once
#include <vector>
#include "Product.h"
#include <array>
#include "Category.h"
class Cart
{
public: 
	Cart();
	void AddProduct(const std::unordered_map<std::string, std::shared_ptr<Category>>& other) noexcept;
	void DeleteProduct() noexcept;
	double ResulPrice() const noexcept;
	std::shared_ptr<Product> GetElementsCart(size_t element);
	size_t getSize() const noexcept;
	void Clear() noexcept;
	
private:
	std::vector<std::shared_ptr<Product>> productList;
	double totalCount = 0;
	
};
