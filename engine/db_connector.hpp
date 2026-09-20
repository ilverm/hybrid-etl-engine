#pragma once

#include <string>

namespace db_connector {
    bool connect_to_db(const std::string& connection);
}