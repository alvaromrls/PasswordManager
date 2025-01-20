#include "PasswordGenerator.h"
#include <random>

void PasswordGenerator::generateCharacterPool()
{
    for (char c = 'a'; c <= 'z'; ++c)
    {
        characterPool.push_back(c);
    }
    if (includeUppercase_)
    {
        for (char c = 'A'; c <= 'Z'; ++c)
        {
            characterPool.push_back(c);
        }
    }
    if (includeNumbers_)
    {
        for (char c = '0'; c <= '9'; ++c)
        {
            characterPool.push_back(c);
        }
    }
    if (includeSpecialChars_)
    {
        for (char c : PASSWORD_GENERATOR_SPECIAL_CHARS)
        {
            characterPool.push_back(c);
        }
    }
}

std::string PasswordGenerator::generatePassword()
{

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, characterPool.size() - 1);

    // Resultado donde se almacenarán las muestras aleatorias
    std::string randomString;

    // Seleccionar N muestras aleatorias, permitiendo repeticiones
    for (size_t i = 0; i < length_; ++i)
    {
        randomString += characterPool[distrib(gen)]; // Añadir al string
    }

    return std::move(randomString);
}