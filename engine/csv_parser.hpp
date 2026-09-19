#pragma once

#include <vector>
#include <string>

namespace csv_parser {
    int add(int i, int j);
    std::vector<std::string> column_parser(std::string_view row);
    std::vector<std::vector<std::string>> read_csv(const std::string& filename, std::size_t first_n_lines = 0);
}