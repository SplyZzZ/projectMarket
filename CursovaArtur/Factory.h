#pragma once
#include <map>
#include <string>
#include <functional>
#include "Product.h"
struct ProductInformation
{
	std::string typeProduct;
	std::string category;
	std::function<std::shared_ptr<Product>()> FactoryMethod;
};
extern std::map<std::string, ProductInformation> productRegisty;