#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(const int i, const int j) {
    return i + j;
}

PYBIND11_MODULE(engine, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 example";
    m.def("add", &add, "A function that adds two numbers");
}