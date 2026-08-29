#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include <string>

namespace py = pybind11;
using namespace pybind11::literals;

namespace {

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
    std::vector<std::vector<std::string>> read_csv(const std::string& filename, const std::size_t first_n_lines = 0) {
        const char* p = filename.c_str();
        const int fd = open(p, O_RDONLY);
        std::vector<std::vector<std::string>> table;

        if (fd == -1) { return std::vector<std::vector<std::string>>{}; }

        // structure of the data returned by the fstat function.
        struct stat buffer{};
        fstat(fd, &buffer);

        void* pa = mmap(nullptr, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);

        if (pa != MAP_FAILED) {
            const auto re = static_cast<const char*>(pa);
            std::size_t row_counter{0};
            for (std::size_t i = 0; i < buffer.st_size; i++) {
                if (re[i] == '\n' || i == buffer.st_size - 1) {
                    if (first_n_lines != 0 && first_n_lines == table.size()) { break; }
                    const std::string_view sv{re + row_counter, i - row_counter};
                    std::vector<std::string> all_rows = column_parser(sv);
                    table.push_back(all_rows);
                    row_counter = i + 1;
                }
            }
        } else { return std::vector<std::vector<std::string>>{}; }

        munmap(pa, buffer.st_size);
        close(fd);

        return table;
    }

}

PYBIND11_MODULE(engine, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 example";
    m.def("add", &add, "A function that adds two numbers");

    m.def("read_csv", &read_csv, "filename"_a, "first_n_lines"_a = 0, "A function that reads a CSV file");
}