#include "DataStorage.h"
#include <iostream>
#include <fstream>
#include <filesystem>

DataStorage::DataStorage(const std::string &filePath) : filePath_{filePath}
{
    loadOrCreate();
}

void DataStorage::loadOrCreate()
{
    bool fileExisted = std::filesystem::exists(filePath_);

    if (fileExisted)
    {
        std::ifstream file(filePath_);
        if (file.is_open())
        {
            file >> data_;
            file.close();
        }
        else
        {
            throw std::runtime_error("Couldn't open");
        }
    }
    else
    {
        std::ofstream file(filePath_);
        if (file.is_open())
        {
            file << "[]";
            data_ = nlohmann::json::object();
            file.close();
        }
        else
        {
            throw std::runtime_error("Couldn't create new file");
        }
    }
}

DataStorage::~DataStorage() {}

void DataStorage::saveUserData(const std::string &username, const UserData &userData)
{
    data_[username] = userData.to_json();
    writeFile();
} // Guarda o actualiza datos de un usuario

void DataStorage::writeFile() // Método interno para escritura
{
    std::ofstream file(filePath_);
    if (file.is_open())
    {
        file << data_.dump(4);
        file.close();
    }
    else
    {
        throw std::runtime_error("Couldn't create new file");
    }
}

bool DataStorage::userExists(const std::string &username) const
{
    return data_.contains(username);
}

std::optional<UserData> DataStorage::getUserData(const std::string &username) const
{
    if (!userExists(username))
    {
        return {};
    }
    try
    {
        UserData user = UserData::from_json(data_[username]);
        return user;
    }
    catch (...)
    {
        return {};
    }
}

void DataStorage::deleteUser(const std::string &username)
{
    if (userExists(username))
    {
        data_.erase(username);
        writeFile();
    }
}
