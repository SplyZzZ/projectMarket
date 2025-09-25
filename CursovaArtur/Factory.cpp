#include "Factory.h"
#include "Phone.h"
#include "TV.h"
#include "Exercise.h"
#include "FleshDrive.h"
std::map<std::string, ProductInformation> productRegisty =
{
	{"Phone", {"Телефон", "Гаджети", []() {return std::make_shared<Phone>();}}},
	{"TV", {"Телевізор", "ДомашняТехніка", []() {return std::make_shared<TV>();}}},
	{"Exercise", {"Зарядка", "Живлення", []() {return std::make_shared<Exercise>();}}},
	{"FleshDrive", {"Флешка", "Пам'ять" ,[]() {return std::make_shared<FleshDrive>();}}}
};

