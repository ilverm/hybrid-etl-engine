#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

#include "csv_parser.hpp"
#include "db_connector.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(engine, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 example";
    m.def("add", &csv_parser::add, "A function that adds two numbers");

    m.def("read_csv", &csv_parser::read_csv, "filename"_a, "first_n_lines"_a = 0, "A function that reads a CSV file");
    m.def("connect_to_db", &db_connector::connect_to_db, "connection", "A function that lets you connect to a db");
    m.def("create_table", &db_connector::create_table, "connection_str", "name_of_table", "columns", "Creates a table from a CSV file");
}