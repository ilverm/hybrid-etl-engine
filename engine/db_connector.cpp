#include <fcntl.h>
#include <iostream>
#include <pqxx/pqxx>
#include <string_view>
#include <vector>
#include <format>
#include <fstream>

#include "csv_parser.hpp"

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

    bool populate_db(const std::string& connection_str, const std::string& table_name, const std::string& file_name) {
        try {
            pqxx::connection cx{connection_str};
            pqxx::work tx{cx};
            pqxx::stream_to stream{pqxx::stream_to::raw_table(tx, table_name)};
            bool is_first_row{true};

            csv_parser::for_each_line(file_name, [&](const std::string_view sv){
                if (is_first_row) {
                    is_first_row = false;
                    return true;
                }

                stream.write_row(csv_parser::column_parser(sv));
                return true;
            });

            stream.complete();
            tx.commit();
            return true;
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

}