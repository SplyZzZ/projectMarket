#pragma once

#include "argon2.h"
#include "Category.h"

#include <iostream>       // std::cin, std::cout
#include <string>         // std::string
#include <unordered_map>  // std::unordered_map
#include <memory>         // std::shared_ptr
#include <limits>         // std::numeric_limits

namespace Security
{
    std::string hashPassword(const std::string& pass);
    bool verifyPassword(const std::string& hash, const std::string& pass);
}

namespace ConsoleHelper
{
    std::string readLine();

    template<typename T>
    auto readNumber(T& number)
    {
        while (true)
        {
            if (std::cin >> number)
                break;

            std::cout << "Некоректне значення! Спробуйте ще раз: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return number;
    }
}

namespace StoreUtils
{
    bool searchCategory(
        const std::unordered_map<std::string, std::shared_ptr<Category>>& map,
        std::string& nameCategory
    );
}
