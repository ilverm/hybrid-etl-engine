#include <pybind11/pybind11.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

#include <string>

namespace py = pybind11;

int add(const int i, const int j) {
    return i + j;
}

// returns a file descriptor
int read_csv(const std::string& filename) {
    const char* p = filename.c_str();
    const int fd = open(p, O_RDONLY);

    if (fd == -1) { return -1; }

    struct stat buffer{};
    fstat(fd, &buffer);

    void* pa = mmap(nullptr, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);

    if (pa != MAP_FAILED) {
        const auto re = static_cast<const char*>(pa);

        for (int i = 0; i < 20; i++) {
            std::cout << re[i] << std::endl;
        }
    } else { return -1; }

    munmap(pa, buffer.st_size);
    close(fd);

    return 0;
}

PYBIND11_MODULE(engine, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 example";
    m.def("add", &add, "A function that adds two numbers");

    m.def("read_csv", &read_csv, "A function that reads a CSV file");
}