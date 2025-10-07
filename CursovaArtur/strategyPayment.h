#pragma once
class IStrategy
{
public:
	virtual void payment() = 0;
	~IStrategy() = default;
};
class Card : public IStrategy
{
	void payment() override;
};
class Crypt : public IStrategy
{

	void payment() override;
};
class Certificate : public IStrategy
{
	void payment() override;
};
class Cash : public IStrategy
{
	void payment() override;
};