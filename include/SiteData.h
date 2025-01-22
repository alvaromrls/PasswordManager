#include <string>
#include <nlohmann/json.hpp>

class SiteData
{
public:
    std::string site;
    std::string password;
    std::string password_salt;

    SiteData() = default;
    SiteData(const std::string &s, const std::string &p, const std::string &ps)
        : site(s), password(p), password_salt(ps) {}

    // Método para serializar el objeto a JSON
    nlohmann::json to_json() const
    {
        return nlohmann::json{
            {"site", site},
            {"password", password},
            {"password_salt", password_salt}};
    }

    // Método para deserializar el objeto desde JSON
    static SiteData from_json(const nlohmann::json &j)
    {
        return SiteData(
            j.at("site").get<std::string>(),
            j.at("password").get<std::string>(),
            j.at("password_salt").get<std::string>());
    }
};
