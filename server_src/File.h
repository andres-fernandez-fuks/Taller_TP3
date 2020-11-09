//
// Created by andy on 8/11/20.
//

#ifndef TP_3_FILE_H
#define TP_3_FILE_H

#include <string>
#include <fstream>
#include "FileException.h"

class File {
public:
    explicit File(const std::string& file_name);
    void getLine(std::string& line);
    bool isEmpty() const;

private:
    std::ifstream infile;
    bool empty = false;
};

#endif //TP_3_FILE_H
