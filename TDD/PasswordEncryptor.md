- [x] **Prueba de inicialización**

* **Objetivo:** Asegurar que la clase se inicializa correctamente con los parámetros proporcionados (clave).
* **Pasos:**
  1. Crear una instancia de `PasswordEncryptor` pasando una clave de encriptación válida.
  2. Verificar que la instancia se crea sin errores.

---

1. [x] **Prueba de salt**

- Verifica que se genera un salt aleatorio de tamaño 10.

---

- [x] **Objetivo:** Verificar que la encriptación funciona correctamente con un texto claro dado.

* **Pasos:**
* 1. Crear una instancia de `PasswordEncryptor`.
  2. Llamar al método de encriptación con un texto claro, por ejemplo, `"password123"`.
  3. Verificar que el resultado no es igual al texto claro.
  4. Comprobar que el resultado es un valor diferente en cada ejecución (ya que debe estar influenciado por el salt).

---

- [x] **Objetivo:** Verificar que el texto encriptado se puede desencriptar correctamente.

- **Pasos:**

  1. Crear una instancia de `PasswordEncryptor` con un salt y clave válidos.
  2. Encriptar un texto claro, por ejemplo, `"password123"`.
  3. Llamar al método de desencriptación con el texto encriptado obtenido en el paso anterior.
  4. Verificar que el texto desencriptado es igual al texto claro original `"password123"`.

---

- [x] **Objetivo:** Asegurar que se lance una excepción si intentamos encriptar sin un salt válido.

- **Pasos:**
  1. Crear una instancia de `PasswordEncryptor` con un salt inválido (tamaño diferente de 10).
  2. Llamar al método de encriptación y verificar que se lance una excepción (`std::invalid_argument` o similar).
  3. Comprobar que la excepción está relacionada con un salt incorrecto.

---

- [x] [ ]

- **Objetivo:** Verificar que la desencriptación falle si se usa un salt incorrecto.
- **Pasos:**
  1. Crear una instancia de `PasswordEncryptor` con un salt válido y encriptar un texto.
  2. Crear una nueva instancia de `PasswordEncryptor` con un salt diferente (incorrecto).
  3. Llamar al método de desencriptación con el texto encriptado y verificar que se lance una excepción o que el resultado no sea el texto claro original.

---

- [x] [ ]

- **Objetivo:** Asegurar que cada encriptación de un mismo texto con el mismo salt produzca resultados diferentes.
- **Pasos:**
  1. Crear una instancia de `PasswordEncryptor`.
  2. Encriptar el mismo texto claro dos veces.
  3. Verificar que el resultado de la encriptación sea diferente en ambas ocasiones.

---

- [x] [ ]

- **Objetivo:** Verificar que la desencriptación falle si el texto encriptado es modificado.
- **Pasos:**
  1. Crear una instancia de `PasswordEncryptor` y encriptar un texto claro.
  2. Modificar el texto encriptado (cambiar un carácter).
  3. Intentar desencriptar el texto modificado y verificar que se lance una excepción o que el resultado sea incorrecto.

---

- [ ]

- **Objetivo:** Asegurar que la encriptación y desencriptación no sean vulnerables a ataques si la contraseña es corta.
- **Pasos:**
  1. Crear una instancia de `PasswordEncryptor` y encriptar una contraseña extremadamente corta (por ejemplo, `"a"`).
  2. Asegurar que el proceso de encriptación y desencriptación no se vea comprometido por la longitud de la contraseña.

---

- [x] [ ]

- **Objetivo:** Verificar que no se acepten valores de salt no válidos (por ejemplo, salt de tamaño 0 o más de 10).
- **Pasos:**
  1. Intentar crear una instancia de `PasswordEncryptor` con un salt de tamaño 0 o mayor a 10.
  2. Verificar que se lance una excepción (`std::invalid_argument` o similar).
  3. Comprobar que el mensaje de error indique que el salt no es válido.

---

- [ ]

- **Objetivo:** Verificar que la clase maneje correctamente claves de encriptación inválidas.
- **Pasos:**
  1. Intentar crear una instancia de `PasswordEncryptor` con una clave de encriptación no válida (por ejemplo, cadena vacía o demasiado corta).
  2. Verificar que se lance una excepción al intentar crear el objeto.
  3. Comprobar que el mensaje de error sea adecuado.

---

- [ ]

- **Objetivo:** Asegurar que se pueda encriptar y desencriptar varias contraseñas simultáneamente sin interferencias.
- **Pasos:**
  1. Crear varias instancias de `PasswordEncryptor` con diferentes saltes y claves.
  2. Encriptar varios textos y luego desencriptarlos.
  3. Verificar que cada desencriptación devuelva el texto claro correcto sin interferencias entre los objetos.

---
