# Establece la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(PasswordManager)

# Establece el estándar de C++
set(CMAKE_CXX_STANDARD 17)

# Incluye directorios de cabeceras
include_directories(include)

# Agrega el submódulo de Google Test (asegúrate de que esté en el subdirectorio 'external/googletest')
add_subdirectory(external/googletest)

# Agrega la fuente de implementación
add_library(UserManager src/UserManager.cpp)

# Agrega las pruebas
enable_testing()
add_executable(UserManagerTests tests/UserManagerTests.cpp)

# Asocia los archivos de prueba con el ejecutable y vincula Google Test
target_link_libraries(UserManagerTests UserManager gtest gtest_main)

# Agrega un target para ejecutar las pruebas
add_test(NAME UserManagerTests COMMAND UserManagerTests)
