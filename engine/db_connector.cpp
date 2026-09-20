#include <iostream>
#include <pqxx/pqxx>
#include <string_view>
#include <vector>
#include <format>

namespace db_connector {
    bool connect_to_db(const std::string& connection) {
        try {
            pqxx::connection cx(connection);
            return true;
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool create_table(const std::string& connection_str, const std::string_view& name_of_table, const std::vector<std::string>& columns) {
        try {
            pqxx::connection cx{connection_str};
            pqxx::work tx{cx};
            std::string sql_cols;
            for (size_t i = 0; i < columns.size(); ++i) {
                sql_cols += std::format("\"{}\" TEXT", columns[i]);
                if (i + 1 < columns.size()) sql_cols += ", ";
            }

            const std::string query{std::format("CREATE TABLE IF NOT EXISTS {} ({})", name_of_table, sql_cols)};
            tx.exec(query);
            tx.commit();
            return true;
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

}