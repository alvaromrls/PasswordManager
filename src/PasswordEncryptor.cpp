#include "PasswordEncryptor.h"
#include "PasswordBuilder.h"
#include <utility>

PasswordEncryptor::PasswordEncryptor(const std::string &encryptionKey) : encryptionKey_{encryptionKey}
{
    PasswordGeneratorBuilder<PasswordGenerator> builder;
    pwgenerator = builder.setLength(ENCRYPTOR_SALT_LENGHT)
                      .includeUppercase(true)
                      .includeSpecialChars(true)
                      .includeNumbers(true)
                      .build();
    ctx_ = EVP_CIPHER_CTX_new();
    if (!ctx_)
    {
        throw std::runtime_error("Something went wrong");
    }
    std::fill(std::begin(key), std::end(key), 0);
    std::fill(std::begin(iv), std::end(iv), 0);
}

void PasswordEncryptor::generateSalt()
{
    // CAMBIO: Validar que el generador no es nulo
    if (!pwgenerator)
    {
        throw std::runtime_error("Password generator not initialized");
    }

    salt_ = std::move(pwgenerator->generatePassword());

    // CAMBIO: Asegurar que el salt tiene el tamaño correcto
    if (salt_.length() != ENCRYPTOR_SALT_LENGHT)
    {
        throw std::runtime_error("Generated salt has an invalid length");
    }
}

std::pair<std::string, std::string> PasswordEncryptor::encryptPassword(const std::string &password)
{
    generateSalt();
    deriveKey();
    return {applyEncryption(password), salt_};
}

void PasswordEncryptor::deriveKey()
{
    const char *password_bytes = encryptionKey_.c_str();
    const unsigned char *salt_bytes = reinterpret_cast<const unsigned char *>(salt_.c_str());

    //  Usar un único llamado a PBKDF2 para mejorar eficiencia
    unsigned char derived_data[ENCRYPTOR_KEY_SIZE + ENCRYPTOR_IV_SIZE];
    if (PKCS5_PBKDF2_HMAC(password_bytes,
                          encryptionKey_.length(),
                          salt_bytes,
                          ENCRYPTOR_SALT_LENGHT,
                          10000,
                          EVP_sha256(),
                          sizeof(derived_data),
                          derived_data) != 1)
    {
        throw std::runtime_error("Failed to derive key and IV");
    }

    // Separar la clave y el IV del resultado de PBKDF2
    std::copy(derived_data, derived_data + ENCRYPTOR_KEY_SIZE, key);
    std::copy(derived_data + ENCRYPTOR_KEY_SIZE, derived_data + sizeof(derived_data), iv);
}

std::string PasswordEncryptor::applyEncryption(const std::string &password)
{

    if (password.length() >= ENCRYPTOR_OUTPUT_SIZE)
    {
        throw std::invalid_argument("Password should be under 128");
    }

    if (EVP_EncryptInit_ex(ctx_, EVP_aes_256_cbc(), nullptr, key, iv) != 1)
        throw std::runtime_error("Something went wrong");

    int len;
    int ciphertext_len;

    if (EVP_EncryptUpdate(ctx_, _buffer, &len,
                          reinterpret_cast<const unsigned char *>(password.c_str()), password.length()) != 1)
        throw std::runtime_error("Something went wrong");

    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx_, _buffer + len, &len) != 1)
        throw std::runtime_error("Something went wrong");
    ciphertext_len += len;

    return std::string{reinterpret_cast<const char *>(_buffer), (size_t)ciphertext_len};
};

std::string PasswordEncryptor::decryptPassword(const std::string &encryptedPassword, const std::string &salt)
{
    if (salt.length() != ENCRYPTOR_SALT_LENGHT)
    {
        throw std::invalid_argument("Salt lenght is wrong!");
    }

    if ((encryptedPassword.length() % ENCRYPTOR_BLOCK_SIZE) != 0)
    {
        {
            throw std::invalid_argument("Encrypted size is wrong");
        }
    }

    salt_ = salt;
    deriveKey();
    return std::move(applyDecryption(encryptedPassword));
}

std::string PasswordEncryptor::applyDecryption(const std::string &encryptedPassword)
{
    if (EVP_DecryptInit_ex(ctx_, EVP_aes_256_cbc(), nullptr, key, iv) != 1)
        throw std::runtime_error("Something went wrong");

    int len;
    int plaintext_len;
    auto *ciphertext = reinterpret_cast<const unsigned char *>(encryptedPassword.c_str());

    if (EVP_DecryptUpdate(ctx_, _buffer, &len, ciphertext, encryptedPassword.length()) != 1)
        throw std::runtime_error("Something went wrong");
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx_, _buffer + len, &len) != 1)
        throw std::runtime_error("Decryption failed");

    plaintext_len += len;

    plaintext_len;
    return std::move(std::string{reinterpret_cast<const char *>(_buffer), (size_t)plaintext_len});
}