#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace csv_parser {
    int add(int i, int j);
    std::vector<std::string> column_parser(std::string_view row);

    template <typename Callback>
    bool for_each_line(const std::string& filename, Callback&& callback) {
        const int fd{open(filename.c_str(), O_RDONLY)};
        if (fd == -1) { return false; }

        struct stat buffer{};
        if (fstat(fd, &buffer) == -1 || buffer.st_size == 0) { close(fd); return false; }

        void* pa = mmap(nullptr, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (pa == MAP_FAILED) { close(fd); return false; }

        const auto re{static_cast<const char*>(pa)};
        std::size_t char_counter{0};

        for (std::size_t i = 0; i < buffer.st_size; i++) {
            if (re[i] == '\n' || i == buffer.st_size - 1) {
                const std::size_t len{re[i] == '\n' ? i - char_counter : i - char_counter + 1};
                const std::string_view sv{re + char_counter, len};
                char_counter = i + 1;
                if (!callback(sv)) { break; }
            }
        }

        munmap(pa, buffer.st_size);
        close(fd);
        return true;
    }

    std::vector<std::vector<std::string>> read_csv(const std::string& filename, std::size_t first_n_lines = 0);
}