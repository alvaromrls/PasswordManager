#pragma once

#include <string>
#include <vector>
#include <stdexcept>

// Constantes
/// Longitud mínima de contraseña permitida.
const int PASSWORD_GENERATOR_MIN_LENGHT = 8;

/// Conjunto de caracteres especiales disponibles para la generación de contraseñas
const std::string PASSWORD_GENERATOR_SPECIAL_CHARS = "!@#$%^&*()-_+=<>?/.,;:[]{}|";

/**
 * @class PasswordGenerator
 * @brief Clase para generar contraseñas aleatorias según configuraciones dadas.
 *
 * Esta clase permite generar contraseñas aleatorias a partir de una longitud especificada y configuraciones opcionales
 * para incluir mayúsculas, caracteres especiales y números.
 *
 * Las contraseñas se generan utilizando un conjunto de caracteres definidos por el usuario, y se aseguran de ser
 * aleatorias utilizando el generador de números aleatorios estándar de C++.
 */
class PasswordGenerator
{
public:
    /**
     * @brief Constructor para crear un generador de contraseñas.
     *
     * Este constructor inicializa el generador de contraseñas con las configuraciones dadas. Si la longitud proporcionada
     * es menor que la longitud mínima permitida (definida por PASSWORD_GENERATOR_MIN_LENGHT), se lanzará una excepción.
     *
     * @param length Longitud de la contraseña a generar. Debe ser mayor o igual a PASSWORD_GENERATOR_MIN_LENGHT.
     * @param includeUppercase Indica si la contraseña debe incluir caracteres en mayúsculas.
     * @param includeSpecialChars Indica si la contraseña debe incluir caracteres especiales.
     * @param includeNumbers Indica si la contraseña debe incluir números.
     *
     * @throws std::invalid_argument Si la longitud es menor que PASSWORD_GENERATOR_MIN_LENGHT.
     */
    PasswordGenerator(int length, bool includeUppercase, bool includeSpecialChars, bool includeNumbers)
        : length_(length), includeUppercase_(includeUppercase),
          includeSpecialChars_(includeSpecialChars), includeNumbers_(includeNumbers)
    {
        if (length_ < PASSWORD_GENERATOR_MIN_LENGHT)
        {
            throw std::invalid_argument("The length is too small");
        }
        generateCharacterPool();
    }

    /**
     * @brief Genera una contraseña aleatoria utilizando las configuraciones actuales.
     *
     * Este método crea una contraseña aleatoria generada a partir del conjunto de caracteres configurado previamente.
     * La contraseña tendrá la longitud especificada en el constructor.
     *
     * @return Una cadena de caracteres que representa la contraseña generada.
     */
    std::string generatePassword();

private:
    /**
     * @brief Genera el conjunto de caracteres posibles que se pueden usar para la contraseña.
     *
     * Este método configura el vector `characterPool` con los caracteres que se pueden utilizar en la generación
     * de la contraseña, dependiendo de las opciones configuradas (minúsculas, mayúsculas, números, caracteres especiales).
     */
    void generateCharacterPool();

    int length_;                     ///< Longitud de la contraseña a generar.
    bool includeUppercase_;          ///< Indica si se deben incluir mayúsculas en la contraseña.
    bool includeSpecialChars_;       ///< Indica si se deben incluir caracteres especiales en la contraseña.
    bool includeNumbers_;            ///< Indica si se deben incluir números en la contraseña.
    std::vector<char> characterPool; ///< Conjunto de caracteres posibles para la contraseña.
};