#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "SiteData.h"

class UserData
{
public:
    std::string password;
    std::string password_salt;
    std::vector<SiteData> data;

    UserData() = default;

    UserData(const std::string &p, const std::string &ps, const std::vector<SiteData> &d)
        : password(p), password_salt(ps), data(d) {}

    // Método para serializar el objeto a JSON
    nlohmann::json to_json() const
    {
        std::vector<nlohmann::json> data_json;
        for (const auto &site : data)
        {
            data_json.push_back(site.to_json());
        }
        return nlohmann::json{
            {"password", password},
            {"password_salt", password_salt},
            {"data", data_json}};
    }

    // Método para deserializar el objeto desde JSON
    static UserData from_json(const nlohmann::json &j)
    {
        std::vector<SiteData> data_vec;
        for (const auto &site_json : j.at("data"))
        {
            data_vec.push_back(SiteData::from_json(site_json));
        }
        return UserData(
            j.at("password").get<std::string>(),
            j.at("password_salt").get<std::string>(),
            data_vec);
    }
};
