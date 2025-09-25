#pragma once
#include "Product.h"
class FleshDrive : public Product
{
public:
	FleshDrive();
	~FleshDrive();
	virtual void GetInformationProduct() const noexcept override;
	virtual void SetInformationProduct() noexcept override;
	
private:
	size_t sizeGB;
};