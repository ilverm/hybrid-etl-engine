#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace db_connector {
    bool connect_to_db(const std::string& connection);
    bool create_table(const std::string& connection_str, const std::string_view& name_of_table, const std::vector<std::string>& columns);
}