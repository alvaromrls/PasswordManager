# Establece la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(PasswordManager)

# Establece el estándar de C++ que se usará
set(CMAKE_CXX_STANDARD 17)

# Usar FetchContent para obtener la librería nlohmann/json
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2  # O la última versión estable
)
FetchContent_MakeAvailable(nlohmann_json)

# Configurar las rutas de OpenSSL de MSYS2 manualmente
set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
set(OPENSSL_LIBRARIES "C:/msys64/mingw64/lib")
set(OPENSSL_INCLUDE_DIR "C:/msys64/mingw64/include")


# Encuentra OpenSSL para asegurar que OpenSSL::Crypto esté disponible
find_package(OpenSSL REQUIRED)
set(OPENSSL_API_COMPAT 0x10100000)  # Usar la compatibilidad de OpenSSL 1.1.1


# Incluir directorios de cabeceras
include_directories(include)
include_directories(${nlohmann_json_SOURCE_DIR}/include)
include_directories(${openssl_SOURCE_DIR}/include)

# Agrega el submódulo de Google Test (asegúrate de que esté en el subdirectorio 'external/googletest')
add_subdirectory(external/googletest)

# Agrega la fuente de implementación
add_library(UserManager src/UserManager.cpp)
add_library(PasswordGenerator src/PasswordGenerator.cpp)
add_library(PasswordEncryptor src/PasswordEncryptor.cpp)
add_library(FileStorage src/FileStorage.cpp)

# Agrega las pruebas
enable_testing()
add_executable(UserManagerTests tests/UserManagerTests.cpp)
add_executable(PasswordGeneratorTests tests/PasswordGeneratorTests.cpp)
add_executable(PasswordBuilderTests tests/PasswordBuilderTests.cpp)
add_executable(FileStorageTests tests/FileStorageTests.cpp)
add_executable(PasswordEncryptorTests tests/PasswordEncryptorTests.cpp)

# Vincula el ejecutable con la librería de UserManager y Google Test
target_link_libraries(UserManagerTests UserManager gtest gtest_main nlohmann_json::nlohmann_json)
target_link_libraries(FileStorageTests FileStorage gtest gtest_main nlohmann_json::nlohmann_json)
target_link_libraries(PasswordGeneratorTests PasswordGenerator gtest gtest_main )
target_link_libraries(PasswordBuilderTests PasswordGenerator gtest gtest_main )
target_link_libraries(PasswordEncryptorTests PasswordEncryptor PasswordGenerator gtest gtest_main )

target_link_libraries(PasswordEncryptor PUBLIC OpenSSL::Crypto)

# Agrega un target para ejecutar las pruebas
add_test(NAME UserManagerTests COMMAND UserManagerTests)
add_test(NAME FileStorageTests COMMAND FileStorageTests)
add_test(NAME PasswordGeneratorTests COMMAND PasswordGeneratorTests)
add_test(NAME PasswordBuilderTests COMMAND PasswordBuilderTests)
add_test(NAME PasswordEncryptorTests COMMAND PasswordEncryptorTests)

# Agrega un ejecutable principal (si es necesario)
add_executable(PasswordManager src/main.cpp)
target_link_libraries(PasswordManager PRIVATE nlohmann_json::nlohmann_json)
