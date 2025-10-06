#pragma once
#include <memory>
class IObserver
{
public:
	virtual void UpDate(size_t status, int ID) = 0;
	virtual ~IObserver() = default;
};
class ISubject
{
public:
	virtual void Notify() = 0;
	virtual ~ISubject() = default;
};