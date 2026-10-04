#include <pybind11/stl.h>
#include <iostream>
#include <string>

#include "csv_parser.hpp"

namespace csv_parser {
    int add(const int i, const int j) { return i + j; }

    std::vector<std::string> column_parser(const std::string_view row) {
        std::vector<std::string> vs{};
        std::string::size_type start{0}, found{};
        std::string word{};
        while (row.find(',', start) != std::string_view::npos) {
            found = row.find(',', start);
            word = row.substr(start, found - start);
            vs.push_back(word);
            start = found + 1;
        }
        word = row.substr(start);
        if (!row.empty()) { vs.push_back(word); }
        return vs;
    }

    // If first_n_lines = 0 -> read all file
    std::vector<std::vector<std::string>> read_csv(const std::string& filename, const std::size_t first_n_lines) {
        std::vector<std::vector<std::string>> table;

        for_each_line(filename, [&](std::string_view sv) {
            if (first_n_lines != 0 && table.size() == first_n_lines) { return false; }
            table.push_back(column_parser(sv));
            return true;
        });
        return table;
    }
}

