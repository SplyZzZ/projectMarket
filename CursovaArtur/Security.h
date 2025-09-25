#pragma once
#include "argon2.h"
namespace Security
{
    std::string hashPassword(const std::string& pass);
    bool verifyPassword(const std::string& hash, const std::string& pass);
   
   
}
namespace ConsoleHelper
{
    std::string readLine();
}
namespace StoreUtils
{
    bool searchCategory(const std::unordered_map<std::string, std::shared_ptr<Category>>& map, std::string& nameCategory);
}
