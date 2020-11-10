//
// Created by andy on 10/11/20.
//

#include <iostream>
#include <string>
#include "InputReader.h"

void InputReader::readStdin(std::stringbuf& buffer) {
    std::string line;
    while (std::getline(std::cin, line)) {
        buffer.sputn(line.c_str(), line.length());
        buffer.sputc('\n');
    }
}
