#include "Category.h"

Category::Category(std::string& name, std::string& description) : name(name), description(description)
{
    ID = ++Unik;
}

void Category::AddProduct(std::shared_ptr<Product> other) noexcept
{
	productMap[other->getID()] = other;
}

void Category::DeleteProduct(const int ID) noexcept
{
	productMap.erase(ID);
}

void Category::GetListProduct() const noexcept
{
    for (auto it = productMap.begin(); it != productMap.end(); ++it)
    {                      
        std::shared_ptr<Product> product = it->second; 
        product->getInformationProduct();   
    }
}

std::shared_ptr<Product> Category::GetProduct(int ID) noexcept
{
    return productMap[ID];
}



std::string Category::getName() const noexcept
{
    return name;
}

int Category::Unik = 0;



