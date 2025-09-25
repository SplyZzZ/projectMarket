#pragma once
#include "Product.h"
class Phone : public Product
{
public:
	Phone();
	~Phone();
	virtual void GetInformationProduct() const noexcept override;
	virtual void SetInformationProduct() noexcept override;
private:
	std::string model;
};

