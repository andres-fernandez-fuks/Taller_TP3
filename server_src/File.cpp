//
// Created by andy on 8/11/20.
//

#include <string>
#include "File.h"

File::File(const std::string& file_name) noexcept(false) : infile(file_name) {
    if (!infile)
        throw(FileException("No se puede acceder al directorio raiz"));
}

void File::getLine(std::string& line) {
    if (!std::getline(infile, line))
        empty = true;
}

bool File::isEmpty() const {
    return empty;
}
