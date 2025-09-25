#pragma once
#include "Product.h"
class TV : public Product
{
public:
	TV();
	~TV();
	virtual void GetInformationProduct() const noexcept override;
	virtual void SetInformationProduct() noexcept override;
private:
	std::string resolution;
};