//
// Created by Anand Malviya on 06/06/25.
//

#include "../include/rdb_parser.hpp"

#include <iostream>



rdb_parser::rdb_parser(const std::string &path) {
    file = std::ifstream(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + path);
    }
}

unsigned char rdb_parser::readByte() {
    char b;
    if(!file.get(b)) {
        throw std::runtime_error("unexpected end of file");
    }

    return static_cast<unsigned char>(b);
}

void rdb_parser::parseSimpleString() {
    unsigned char byte;
    byte = readByte();
    int key_len = static_cast<int>(byte);
    std::string key(key_len, '\0');
    file.read(&key[0], key_len);

    //file.get(reinterpret_cast<char&>(byte));
    byte = readByte();
    int val_len = static_cast<int>(byte);
    std::string value(val_len, '\0');
    file.read(&value[0], val_len);

    std::cout << "Key: " << key << ", Value: " << value << std::endl;
}


void rdb_parser::parseHeader() {
    char header[9];
    file.read(header, 9);

    if(file.gcount() != 9) {
        throw std::runtime_error("header too short");
    }

    std::string magic(header, 5);
    std::string version_str(header+5, 4);

    if(magic != "REDIS") {
        throw std::runtime_error("Invalid RDB Header\n");
    }
    int version = std::stoi(version_str);
    std::cout << "RDB version: " << version << std::endl;

}

void rdb_parser::parseMetadata() {

    unsigned char byte;

    // 1. Read until we find 0xFA
    while(file.get(reinterpret_cast<char&>(byte))) {
        if(byte == 0xFA) {
            std::cout << "RDB metadata starts at FA: " << std::hex << (int)byte << std::endl;
            break;
        }
    }

    // 2. Now read the **key length**
    file.get(reinterpret_cast<char&>(byte));
    int key_len = static_cast<int>(byte);
    std::cout << "keylen: " << std::dec << key_len << std::endl;

    // 3. Read the key
    std::string key(key_len, '\0');
    file.read(&key[0], key_len);
    std::cout << "key: " << key << std::endl;

    // 4. Read the **value length**
    file.get(reinterpret_cast<char&>(byte));
    int val_len = static_cast<int>(byte);
    std::cout << "val len: " << val_len << std::endl;

    // 5. Read the value
    std::string value(val_len, '\0');
    file.read(&value[0], val_len);
    std::cout << "value: " << value << std::endl;
}

void rdb_parser::parseDatabase() {
    unsigned char byte = readByte();
    //file.get(reinterpret_cast<char&>(byte));

    if(byte == 0xFE) {

        //file.get(reinterpret_cast<char&>(byte));
        byte = readByte();
        std::cout << "at database" << static_cast<int>(byte) << std::endl;
    }
    //file.get(reinterpret_cast<char&>(byte));
    byte = readByte();
    if(byte == 0xFB) {
        //byte = readByte();
        hashSize = readByte();
        std::cout << "hash size: " << static_cast<int>(hashSize) << std::endl;

        //byte = readByte();
        exp_hashSize = readByte();
        std::cout << "exp hash size: " << static_cast<int>(exp_hashSize) << std::endl;

        byte = readByte();

    }

    while(byte != 0xFF) {
        if(byte == 0x00) {
            parseSimpleString();
        }else {
            std::cout << "Unknown or unhandled object type: 0x" << std::hex << (int)byte << std::endl;
        }
        byte = readByte();
    }
}






