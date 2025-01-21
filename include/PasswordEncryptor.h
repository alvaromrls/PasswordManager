#include <string>
#include <stdexcept>
#include <random>
#include "PasswordGenerator.h"
#include <memory>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/pem.h>

constexpr int ENCRYPTOR_SALT_LENGHT = 10;
constexpr int ENCRYPTOR_OUTPUT_SIZE = 128;
constexpr int ENCRYPTOR_IV_SIZE = 16;
constexpr int ENCRYPTOR_BLOCK_SIZE = 16;
constexpr int ENCRYPTOR_KEY_SIZE = 32;

class PasswordEncryptor
{
public:
    // Constructor: Recibe una clave de encriptación
    PasswordEncryptor(const std::string &encryptionKey);
    ~PasswordEncryptor()
    {
        EVP_CIPHER_CTX_free(ctx_);
    }

    // Método para encriptar una contraseña: devuelve la contraseña encriptada y salt.
    std::pair<std::string, std::string> encryptPassword(const std::string &password);

    // Método para desencriptar una contraseña
    std::string decryptPassword(const std::string &encryptedPassword, const std::string &salt);

    // Método para obtener el salt
    std::string getSalt() const { return salt_; }

    // Función para generar un salt aleatorio de tamaño 10
    void generateSalt();

private:
    // Función para generar el IV (Vector de Inicialización)
    void deriveKey();

    // Función privada de encriptación (por ejemplo, AES)
    std::string applyEncryption(const std::string &password);

    // Función privada de desencriptación (por ejemplo, AES)
    std::string applyDecryption(const std::string &encryptedPassword);

    std::string encryptionKey_;                     // Clave de encriptación
    std::string salt_;                              // Salt
    std::unique_ptr<PasswordGenerator> pwgenerator; // Pointer to a random generator
    unsigned char key[ENCRYPTOR_KEY_SIZE];          // AES-256 -> 32 bytes para la clave
    unsigned char iv[ENCRYPTOR_IV_SIZE];            // AES-CBC -> 16 bytes para el IV
    unsigned char _buffer[ENCRYPTOR_OUTPUT_SIZE];   // OUTPUT STRING
    EVP_CIPHER_CTX *ctx_;                           // context
};
