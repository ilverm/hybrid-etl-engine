#include <iostream>
#include <pqxx/pqxx>

namespace db_connector {
    bool connect_to_db(const std::string& connection) {
        try {
            pqxx::connection cx(connection);
            return true;
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }
}