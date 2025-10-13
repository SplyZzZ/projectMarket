#include "Factory.h"
#include "Phone.h"
#include "TV.h"
#include "Exercise.h"
#include "FleshDrive.h"
std::map<std::string, ProductInformation> productRegisty =
{
	{"Phone", {"Телефон", "Gadgets", []() {return std::make_shared<Phone>();}}},
	{"TV", {"Телевізор", "Home Appliances", []() {return std::make_shared<TV>();}}},
	{"Exercise", {"Зарядка", "Power supply", []() {return std::make_shared<Exercise>();}}},
	{"FleshDrive", {"Флешка", "Memory" ,[]() {return std::make_shared<FleshDrive>();}}}
};

