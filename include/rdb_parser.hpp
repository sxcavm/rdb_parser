//
// Created by Anand Malviya on 06/06/25.
//

#ifndef RDB_PARSER_HPP
#define RDB_PARSER_HPP
#include <string>
#include <fstream>

class rdb_parser {
public:
    rdb_parser(const std::string& path);
    void parseHeader();
    void parseMetadata();
    void parseDatabase();


private:
    std::ifstream file;
    unsigned char hashSize;
    unsigned char exp_hashSize;
    unsigned char readByte();
    void parseSimpleString();
};




#endif //RDB_PARSER_HPP
