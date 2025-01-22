#include "UserData.h"
#include <optional>

class DataStorage
{
public:
    // Constructor que recibe el archivo de datos
    explicit DataStorage(const std::string &filePath);

    // --- Operaciones relacionadas con usuarios ---
    bool userExists(const std::string &username) const;                       // Verifica si un usuario existe
    std::optional<UserData> getUserData(const std::string &username) const;   // Carga los datos de un usuario
    void saveUserData(const std::string &username, const UserData &userData); // Guarda o actualiza datos de un usuario
    void deleteUser(const std::string &username);                             // Elimina un usuario del almacenamiento

    ~DataStorage(); // Destructor para liberar recursos, si aplica

private:
    std::string filePath_; // Ruta al archivo de almacenamiento
    nlohmann::json data_;
    // Métodos auxiliares internos
    void loadOrCreate(); // Carga el archivo o crea uno vacío si no existe
    void writeFile();    // Método interno para escritura
};
