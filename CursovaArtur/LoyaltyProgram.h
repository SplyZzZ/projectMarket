#pragma once
class LoyaltyProgram
{
public:
	LoyaltyProgram();
	void addPurchase(size_t size) noexcept;
	bool removePurchase(size_t size) noexcept;
	size_t getPurchaseCount() const noexcept;

private:
	size_t count;

};
