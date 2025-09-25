#pragma once
#include "Product.h"
class Exercise : public Product
{
public:
	Exercise();
	~Exercise();
	virtual void GetInformationProduct() const noexcept override;
	virtual void SetInformationProduct() noexcept override;
private:
	std::string type;
};

