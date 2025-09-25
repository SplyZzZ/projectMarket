#include "FleshDrive.h"

FleshDrive::FleshDrive() : Product()
{
	sizeGB = 0;
}
FleshDrive::~FleshDrive(){}
void FleshDrive::GetInformationProduct() const noexcept
{
	Product::GetInformationProduct();
	std::cout << "GB: " << sizeGB << std::endl;
}
void FleshDrive::SetInformationProduct() noexcept
{
	Product::SetInformationProduct();
	std::cout << "Введіть розмір флешки в гігабайтах: ";
	std::cin >> sizeGB;
}