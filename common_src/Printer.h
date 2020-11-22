//
// Created by andy on 10/11/20.
//

#ifndef TP_3_PRINTER_H
#define TP_3_PRINTER_H

#include <sstream>
#include <string>
#include <mutex>

class Printer {
public:
    void print(const std::string& output);
private:
    std::mutex m;
};


#endif //TP_3_PRINTER_H
