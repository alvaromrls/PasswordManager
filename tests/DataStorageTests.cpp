#include <gtest/gtest.h>
#include "DataStorage.h"
#include <fstream>
#include <iostream>
#include <cstdio> // Para la función remove()

TEST(DataStorageTest, InstanciacionRutaValida)
{
    std::string existing_file{"my_file.json"};
    std::ofstream file_exist(existing_file);
    if (file_exist.is_open())
    {
        file_exist << "[]";
        file_exist.close();
    }
    else
    {
        ASSERT_TRUE(false) << "Could not create file";
    }
    ASSERT_TRUE(true);

    ASSERT_NO_THROW(DataStorage{existing_file});

    if (remove(existing_file.c_str()) != 0)
    {
        ASSERT_TRUE(false) << "Could not delete fail";
    }
}

class DataStorageTestEmpty : public ::testing::Test
{
protected:
    std::string invented_file;

    // Constructor: configura el entorno del test
    DataStorageTestEmpty() : invented_file("data_base.json")
    {
        // Asegurarnos de que el archivo no exista antes de cada test
        if (std::filesystem::exists(invented_file))
        {
            std::filesystem::remove(invented_file);
        }
    }

    // Destructor: limpia el entorno del test
    ~DataStorageTestEmpty() override
    {
        // Eliminar el archivo creado durante el test
        if (std::filesystem::exists(invented_file))
        {
            std::filesystem::remove(invented_file);
        }
    }
};

// Test específico para comprobar el comportamiento con un archivo vacío
TEST_F(DataStorageTestEmpty, CargaVacia)
{

    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    DataStorage storage{invented_file};

    // Leer el contenido del archivo
    std::ifstream file{invented_file};
    ASSERT_TRUE(file.is_open()) << "Could not open file";

    std::string data{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    file.close();

    // Comprobar que el contenido es un array vacío
    ASSERT_EQ(data, "[]");
}

// Test específico para comprobar el comportamiento de guardar un user
TEST_F(DataStorageTestEmpty, GuardarUsuario)
{
    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    DataStorage storage{invented_file};

    // Crear datos
    std::vector<SiteData> sites{};
    sites.push_back({"amazon", "aaAAaa", "salt1"});
    sites.push_back({"google", "ggGGgg", "salt2"});
    UserData user_data{"mypass", "mysalt", sites};

    storage.saveUserData("alvaro", user_data);

    // Leer el JSON del archivo y deserializarlo
    std::ifstream input_file(invented_file);
    nlohmann::json j2;
    input_file >> j2;
    input_file.close();

    // Crear un objeto UserData desde el JSON
    UserData user_from_json = UserData::from_json(j2["alvaro"]);
    ASSERT_EQ(user_from_json.password, "mypass");
    ASSERT_EQ(user_from_json.password_salt, "mysalt");
    ASSERT_EQ(user_from_json.data.size(), 2);
}

class DataStorageTestWithData : public ::testing::Test
{
protected:
    std::string invented_file;

    // Constructor: configura el entorno del test
    DataStorageTestWithData() : invented_file("data_base.json")
    {
        // Asegurarnos de que el archivo no exista antes de cada test
        if (std::filesystem::exists(invented_file))
        {
            std::filesystem::remove(invented_file);
        }

        // Crear un objeto JSON con 4 usuarios de ejemplo
        nlohmann::json data = {
            {"user1", {{"password", "hashed_password1"}, {"password_salt", "unique_salt1"}, {"data", {{{"site", "web1"}, {"password", "encrypted_password1"}, {"password_salt", "site_specific_salt1"}}}}}},
            {"user2", {{"password", "hashed_password2"}, {"password_salt", "unique_salt2"}, {"data", {{{"site", "web2"}, {"password", "encrypted_password2"}, {"password_salt", "site_specific_salt2"}}}}}},
            {"user3", {{"password", "hashed_password3"}, {"password_salt", "unique_salt3"}, {"data", {{{"site", "web3"}, {"password", "encrypted_password3"}, {"password_salt", "site_specific_salt3"}}}}}},
            {"user4", {{"password", "hashed_password4"}, {"password_salt", "unique_salt4"}, {"data", {{{"site", "web4"}, {"password", "encrypted_password4"}, {"password_salt", "site_specific_salt4"}}}}}}};

        // Escribir los datos JSON en el archivo
        std::ofstream file{invented_file};
        file << data.dump(4); // Usamos `dump(4)` para obtener un JSON formateado con 4 espacios de indentación
        file.close();
    }

    // Destructor: limpia el entorno del test
    ~DataStorageTestWithData() override
    {
        // Eliminar el archivo creado durante el test
        if (std::filesystem::exists(invented_file))
        {
            std::filesystem::remove(invented_file);
        }
    }
};

// Test específico para comprobar el comportamiento de guardar un user
TEST_F(DataStorageTestWithData, UserExists)
{
    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    DataStorage storage{invented_file};

    ASSERT_TRUE(storage.userExists("user1"));
    ASSERT_TRUE(storage.userExists("user2"));
}

// Test específico para comprobar el comportamiento de guardar un user
TEST_F(DataStorageTestWithData, UserDoesntExist)
{
    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    DataStorage storage{invented_file};

    ASSERT_FALSE(storage.userExists("user5"));
}

// Test específico para comprobar el comportamiento de cargar un user
TEST_F(DataStorageTestWithData, CheckUser)
{
    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    DataStorage storage{invented_file};
    UserData u = storage.getUserData("user1").value();
    ASSERT_EQ(u.password, "hashed_password1");
}

// Test específico para comprobar el comportamiento de cargar un user
TEST_F(DataStorageTestWithData, CheckWrongUser)
{
    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    DataStorage storage{invented_file};
    auto user = storage.getUserData("user15").has_value();
    ASSERT_FALSE(user);
}

// Test específico para comprobar el comportamiento de eliminar un user
TEST_F(DataStorageTestWithData, DeleteUser)
{
    // Crear y cerrar el almacenamiento, que debería crear un archivo vacío
    {
        DataStorage storage{invented_file};
        storage.deleteUser("user2");
    }
    DataStorage storage{invented_file};
    ASSERT_FALSE(storage.userExists("user2"));
}
