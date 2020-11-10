//
// Created by andy on 10/11/20.
//

#include <iostream>
#include "Printer.h"
#define CHUNK_SIZE 64

void Printer::print(std::stringbuf& buffer) {
    size_t len = buffer.str().length();
    size_t counter = 0;
    char aux_buffer[CHUNK_SIZE+1];
    while (counter < len) {
        int written = buffer.sgetn(aux_buffer, CHUNK_SIZE);
        aux_buffer[written] = '\0';
        std::cout << aux_buffer;
        counter += written;
    }
}
