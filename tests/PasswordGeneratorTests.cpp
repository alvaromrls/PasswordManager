#include "gtest/gtest.h"
#include "PasswordGenerator.h"
#include <algorithm>

bool isLowerCase(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), [](unsigned char c)
                       {
                           return std::islower(c); // Verifica si el carácter es minúscula
                       });
}

bool isLetter(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), [](unsigned char c)
                       { return std::isalpha(c); });
}

bool hasAtLeastOneUpperCase(const std::string &str)
{
    return std::any_of(str.begin(), str.end(), [](unsigned char c)
                       {
                           return std::isupper(c); // Verifica si el carácter es una mayúscula
                       });
}

// Función auxiliar para verificar que la contraseña tiene al menos un número
bool hasAtLeastOneDigit(const std::string &str)
{
    return std::any_of(str.begin(), str.end(), [](unsigned char c)
                       {
                           return std::isdigit(c); // Verifica si el carácter es un número
                       });
}

// Función auxiliar para verificar que la contraseña tiene al menos un carácter especial
bool hasAtLeastOneSpecialCharacter(const std::string &str)
{
    return std::any_of(str.begin(), str.end(), [](unsigned char c)
                       {
                           return PASSWORD_GENERATOR_SPECIAL_CHARS.find(c) != std::string::npos; // Verifica si el carácter es especial
                       });
}

// Test de generación de contraseña solo con minúsculas
TEST(PasswordGeneratorTest, CanGenerateOnlyLowerCase)
{
    PasswordGenerator pg{100, false, false, false};
    std::string password = pg.generatePassword();
    EXPECT_TRUE(isLowerCase(password));             // Verifica que toda la contraseña esté en minúsculas
    EXPECT_EQ(password.length(), 100);              // Verifica que la longitud sea 100
    EXPECT_FALSE(hasAtLeastOneUpperCase(password)); // Verifica que haya al menos una mayúscula
}

// Test de generación de contraseña con letras (minúsculas o mayúsculas)
TEST(PasswordGeneratorTest, CanGenerateUpperCase)
{
    PasswordGenerator pg{100, true, false, false};
    std::string password = pg.generatePassword();
    EXPECT_TRUE(isLetter(password));               // Verifica que toda la contraseña sean letras
    EXPECT_EQ(password.length(), 100);             // Verifica que la longitud sea 100
    EXPECT_TRUE(hasAtLeastOneUpperCase(password)); // Verifica que haya al menos una mayúscula
}

TEST(PasswordGeneratorTest, CanGeneratePasswordWithAllCharacterTypes)
{
    // Configuración del generador para incluir mayúsculas, minúsculas, números y caracteres especiales
    PasswordGenerator pg{200, true, true, true};
    std::string password = pg.generatePassword();

    // Verifica que la contraseña generada contenga al menos una mayúscula
    EXPECT_TRUE(hasAtLeastOneUpperCase(password)); // Al menos una mayúscula

    // Verifica que la contraseña generada contenga al menos un número
    EXPECT_TRUE(hasAtLeastOneDigit(password)); // Al menos un número

    // Verifica que la contraseña generada contenga al menos un carácter especial
    EXPECT_TRUE(hasAtLeastOneSpecialCharacter(password)); // Al menos un carácter especial

    // Verifica que la longitud de la contraseña sea la esperada
    EXPECT_EQ(password.length(), 200); // Verifica que la longitud sea 12
}

void WillFail(int len)
{
    PasswordGenerator pg{len, true, true, true};
}

TEST(PasswordGeneratorTest, InvalidLength)
{
    // Verifica que lanzar una longitud negativa o demasiado corta lance una excepción
    EXPECT_THROW(WillFail(-1), std::invalid_argument);
    EXPECT_THROW(WillFail(3), std::invalid_argument);
}