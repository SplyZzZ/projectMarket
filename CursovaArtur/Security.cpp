
#include "ElectronicsStore.h"
#include "Security.h"
std::string Security::hashPassword(const std::string& pass)
{
    unsigned char salt[16];
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < 16; ++i)
        salt[i] = std::rand() % 256;


    char encoded[128];


    int result = argon2i_hash_encoded(
        2,
        1 << 16,
        1,
        pass.c_str(), pass.size(),
        salt, sizeof(salt),
        32,
        encoded, sizeof(encoded)
    );

    if (result != ARGON2_OK)
        throw std::runtime_error(argon2_error_message(result));

    return std::string(encoded);
}
bool Security::verifyPassword(const std::string& hash, const std::string& pass)
{
    int result = argon2i_verify(hash.c_str(), pass.c_str(), pass.size());
    return result == ARGON2_OK;
}
std::string ConsoleHelper::readLine()
{
    std::string Line;
    std::getline(std::cin >> std::ws, Line);
    return Line;
}
bool StoreUtils::searchCategory(const std::unordered_map<std::string, std::shared_ptr<Category>>& map, std::string& nameCategory)
{
    return map.find(nameCategory) != map.end();
}
