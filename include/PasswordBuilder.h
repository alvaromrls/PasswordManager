#pragma once

#include <string>
#include <vector>
#include <memory> // Para std::unique_ptr
#include <type_traits>
#include "PasswordGenerator.h"

/**
 * @class PasswordGeneratorBuilder
 * @brief Builder genérico para crear instancias de PasswordGenerator o clases derivadas.
 *
 * Este builder sigue el patrón de diseño Builder para configurar y construir objetos de tipo
 * PasswordGenerator o clases que hereden de él. Utiliza SFINAE para restringir el tipo `T` a
 * ser `PasswordGenerator` o una clase derivada.
 *
 * @tparam T Clase objetivo que debe derivar de PasswordGenerator.
 */
template <typename T, typename = typename std::enable_if<std::is_base_of<PasswordGenerator, T>::value>::type>
class PasswordGeneratorBuilder
{
public:
    /**
     * @brief Configura la longitud de la contraseña a generar.
     *
     * @param length Longitud deseada para la contraseña.
     * @return Referencia al builder actual para encadenar configuraciones.
     */
    PasswordGeneratorBuilder &setLength(int length)
    {
        length_ = length;
        return *this;
    }

    /**
     * @brief Habilita o deshabilita la inclusión de letras mayúsculas en la contraseña.
     *
     * @param value `true` para incluir mayúsculas, `false` para no incluirlas.
     * @return Referencia al builder actual para encadenar configuraciones.
     */
    PasswordGeneratorBuilder &includeUppercase(bool value)
    {
        includeUppercase_ = value;
        return *this;
    }

    /**
     * @brief Habilita o deshabilita la inclusión de caracteres especiales en la contraseña.
     *
     * @param value `true` para incluir caracteres especiales, `false` para no incluirlos.
     * @return Referencia al builder actual para encadenar configuraciones.
     */
    PasswordGeneratorBuilder &includeSpecialChars(bool value)
    {
        includeSpecialChars_ = value;
        return *this;
    }

    /**
     * @brief Habilita o deshabilita la inclusión de números en la contraseña.
     *
     * @param value `true` para incluir números, `false` para no incluirlos.
     * @return Referencia al builder actual para encadenar configuraciones.
     */
    PasswordGeneratorBuilder &includeNumbers(bool value)
    {
        includeNumbers_ = value;
        return *this;
    }

    /**
     * @brief Construye y devuelve una instancia de `T` configurada con los parámetros especificados.
     *
     * @return std::unique_ptr<T> Puntero único a la instancia creada de la clase `T`.
     */
    std::unique_ptr<T> build()
    {
        return std::make_unique<T>(length_, includeUppercase_, includeSpecialChars_, includeNumbers_);
    }

private:
    int length_ = PASSWORD_GENERATOR_MIN_LENGHT; ///< Longitud predeterminada para la contraseña.
    bool includeUppercase_ = false;              ///< Indica si se deben incluir mayúsculas.
    bool includeSpecialChars_ = false;           ///< Indica si se deben incluir caracteres especiales.
    bool includeNumbers_ = false;                ///< Indica si se deben incluir números.
};
