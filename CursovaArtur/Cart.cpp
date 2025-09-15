#include "Cart.h"
#include <Windows.h>
#include "Customer.h"
Cart::Cart() : totalCount(0)
{
};
void Cart::AddProduct(const std::unordered_map<std::string, std::shared_ptr<Category>>& other) noexcept
{
			for (auto it = other.begin(); it != other.end(); ++it)
			{
				std::shared_ptr<Category> category = it->second;
				category->getName();
			}
			std::string option;
			std::cin.ignore();
			std::getline(std::cin, option);
			
			other.at(option)->GetListProduct();
			int towarID;
			std::cin >> towarID;
			productList.push_back(other.at(option)->GetProduct(towarID));
			totalCount += other.at(option)->GetProduct(towarID)->getPrice();
			std::cout << "Greate!";
			Sleep(4000);
			system("CLS");
}
void Cart::DeleteProduct() noexcept
{
	if (productList.size() == 0) { std::cout << "Shopping cart empty"; return; }
	for (size_t i = 0; i < productList.size(); ++i)
	{
		std::cout << i + 1 << " ";
		productList[i]->getInformationProduct();
	}
	std::cout << "Enter the number of the item you wish to delete: ";
	size_t option = 0;
	std::cin >> option; 
	totalCount -= productList[option - 1]->getPrice();
	productList.erase(productList.begin() + (option - 1));
	std::cout << "Item successfully deleted";
}
double Cart::ResulPrice() const noexcept
{
	return totalCount;
}
std::shared_ptr<Product> Cart::GetElementsCart(size_t element)
{
	return productList[element];
}
size_t Cart::getSize() const noexcept
{
	return productList.size();
}
void Cart::Clear() noexcept
{
	if (productList.size() == 0) return;
	totalCount = 0;
	productList.clear();
	productList.shrink_to_fit();
}
