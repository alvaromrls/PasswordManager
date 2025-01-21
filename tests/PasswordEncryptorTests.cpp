#include "gtest/gtest.h"
#include "PasswordEncryptor.h"
#include <iomanip>

TEST(PasswordEncryptorTest, ConstructorTest)
{
    std::string key{"mykey_is_very_strong"};
    PasswordEncryptor encryptor{key};
    ASSERT_NO_THROW(PasswordEncryptor{key});
}

TEST(PasswordEncryptorTest, SaltGenerateTest)
{
    std::string key{"mykey_is_very_strong"};
    PasswordEncryptor encryptor{key};
    ASSERT_EQ(encryptor.getSalt(), "");
    encryptor.generateSalt();
    std::string salt = encryptor.getSalt();
    ASSERT_NE(salt, "");
    ASSERT_EQ(salt.length(), ENCRYPTOR_SALT_LENGHT);
    encryptor.generateSalt();
    ASSERT_NE(salt, encryptor.getSalt());
}

// Calcula la longitud esperada del texto cifrado en función del tamaño de entrada
size_t calculateExpectedCiphertextLength(const std::string &plaintext, size_t blockSize = 16)
{
    return (plaintext.length() / blockSize + (plaintext.length() % blockSize != 0)) * blockSize;
}

TEST(PasswordEncryptorTest, EncryptValidText)
{
    std::string key{"mykey_is_very_strong"};
    std::string og_password{"iliketrains_t_iliketrains"};
    PasswordEncryptor encryptor{key};
    std::pair<std::string, std::string> result = encryptor.encryptPassword(og_password);
    auto [encripted_pw, salt] = result;

    ASSERT_EQ(encryptor.getSalt(), salt);
    ASSERT_NE(encripted_pw, og_password);
    ASSERT_EQ(encripted_pw.length(), calculateExpectedCiphertextLength(og_password)) << "Wrong output size!";
}

TEST(PasswordEncryptorTest, DecryptValidText)
{
    std::string key{"mykey_is_very_strong"};
    std::string og_password{"this_is_my_life"};
    PasswordEncryptor encryptor{key};
    std::pair<std::string, std::string> result = encryptor.encryptPassword(og_password);
    auto [encripted_pw, salt] = result;

    std::string re_password = encryptor.decryptPassword(encripted_pw, salt);
    ASSERT_EQ(re_password, og_password);
}

TEST(PasswordEncryptorTest, WrongSaltException)
{
    std::string key{"mykey_is_very_strong"};
    std::string og_password{"this_is_my_life"};
    PasswordEncryptor encryptor{key};
    std::pair<std::string, std::string> result = encryptor.encryptPassword(og_password);
    auto [encripted_pw, salt] = result;

    ASSERT_THROW(encryptor.decryptPassword(encripted_pw, "sae"), std::invalid_argument);
}

TEST(PasswordEncryptorTest, DecryptWithWrongSalt)
{
    std::string key{"mykey_is_very_strong"};
    std::string og_password{"this_is_my_life"};
    PasswordEncryptor encryptor{key};
    std::pair<std::string, std::string> result = encryptor.encryptPassword(og_password);
    auto [encripted_pw, salt] = result;
    ASSERT_THROW(encryptor.decryptPassword(encripted_pw, "this_is__f"), std::runtime_error);
}

TEST(PasswordEncryptorTest, DiferentTimeDiferentResult)
{
    std::string key{"mykey_is_very_strong"};
    std::string og_password{"this_is_my_life"};
    PasswordEncryptor encryptor{key};
    std::pair<std::string, std::string> result = encryptor.encryptPassword(og_password);
    std::pair<std::string, std::string> result2 = encryptor.encryptPassword(og_password);
    auto [encripted_pw, salt] = result;
    auto [encripted_pw_2, salt_2] = result2;
    ASSERT_NE(salt, salt_2);
    ASSERT_NE(encripted_pw, encripted_pw_2);
}

TEST(PasswordEncryptorTest, Overflow)
{
    std::string key{"mykey_is_very_strong"};
    std::string og_password = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{}|;:',.<>?/~`ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    PasswordEncryptor encryptor{key};
    ASSERT_THROW(encryptor.encryptPassword(og_password), std::invalid_argument);
}
