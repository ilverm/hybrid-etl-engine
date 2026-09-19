#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

#include "csv_parser.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(engine, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 example";
    m.def("add", &csv_parser::add, "A function that adds two numbers");

    m.def("read_csv", &csv_parser::read_csv, "filename"_a, "first_n_lines"_a = 0, "A function that reads a CSV file");
}