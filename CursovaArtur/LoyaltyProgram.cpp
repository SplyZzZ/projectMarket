#include "LoyaltyProgram.h"

LoyaltyProgram::LoyaltyProgram() : count(0)
{}

void LoyaltyProgram::addPurchase(size_t size) noexcept
{
	count += size;
}

bool LoyaltyProgram::removePurchase(size_t size) noexcept
{
	if (count < size) return false;
	count -= size;
	return true;
}

size_t LoyaltyProgram::getPurchaseCount() const noexcept
{
	return count;
}
