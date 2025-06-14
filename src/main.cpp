#include <iostream>
#include <filesystem>

#include "../include/rdb_parser.hpp"

namespace fs = std::filesystem;

std::optional<std::string> get_arg_value(int argc, char** argv, std::string flag) {
    for(int i = 1; i < argc - 1; ++i) {
        if(argv[i] == flag) {
            return argv[i + 1];
        }
    }
    return std::nullopt;
}


int main(int argc, char** argv) {
    /*
    std::optional<std::string> dir = get_arg_value(argc, argv, "--dir");
    std::optional<std::string> dbfilename = get_arg_value(argc, argv, "--dbfilename");

    if(dir.has_value() && dbfilename.has_value()) {
        std::string fullpath = dir.value() + "/" + dbfilename.value();

    }
    */

    auto rdbobj = rdb_parser("/Users/anandmalviya08/CLionProjects/rdb-parser/src/mock_rdb_full.rdb");
    rdbobj.parseHeader();
    rdbobj.parseMetadata();
    rdbobj.parseDatabase();

    return 0;
}
