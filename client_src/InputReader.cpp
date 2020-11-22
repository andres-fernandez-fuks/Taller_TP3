//
// Created by andy on 10/11/20.
//

#include <iostream>
#include <string>
#include "InputReader.h"

void InputReader::readStdin(std::stringstream& buffer) {
    std::string line;
    while (std::getline(std::cin, line)) {
        buffer.write(line.c_str(), line.length());
        buffer.put('\n');
    }
}
