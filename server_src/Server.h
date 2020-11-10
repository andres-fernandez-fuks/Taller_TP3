//
// Created by andy on 10/11/20.
//

#ifndef TP_3_SERVER_H
#define TP_3_SERVER_H

#include <string>

class Server {
public:
    static int handleRequests(const std::string& port,
                       const std::string& info_file);
};


#endif //TP_3_SERVER_H
