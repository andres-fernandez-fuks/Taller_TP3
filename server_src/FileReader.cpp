//
// Created by andy on 8/11/20.
//

#include "FileReader.h"
#include <string>
#include "File.h"

std::string FileReader::getDefaultResponse(const std::string& file_path) {
    try {
        File file(file_path);
        std::string response;
        std::string line;
        while (!file.isEmpty()) {
            file.getLine(line);
            response += line +'\n';
        }
        response = response.substr(0, response.size()-1);
        return response;
    }
    catch(...) {
        throw;
    }
}
