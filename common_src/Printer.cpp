//
// Created by andy on 10/11/20.
//

#include <iostream>
#include <string>
#include "Printer.h"
#define CHUNK_SIZE 64

void Printer::print(const std::string& output) {
    m.lock();
    std::cout << output.c_str();
    m.unlock();
}
