//
// Created by shae on 11/20/17.
//

#include "ioutil.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string readAllText(const std::string &file_path) {
    try {
        std::ifstream file_stream;
        file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file_stream.open(file_path);
        std::stringstream sstream;
        sstream << file_stream.rdbuf();
        file_stream.close();
        return sstream.str();
    }
    catch (std::ifstream::failure &exception) {
        std::cout << "ERROR::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        std::cout << exception.what() << std::endl;
    }
    return std::string();
}
