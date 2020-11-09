//
// Created by andy on 7/11/20.
//

#ifndef TP_3_SERVER_H
#define TP_3_SERVER_H

#include <vector>
#include <atomic>
#include <string>
#include "Thread.h"
#include "../common_src/Socket.h"
#include "ClientHandler.h"


class Server : public Thread {
public:
    Server(std::string port, std::string info_file);
    ~Server() override;
    void run() override;
    void stopConnections();
    void cleanConnections();
    void closeAllConnections();
private:
    Socket socket = Socket(1);
    std::atomic<bool> keep_talking;
    std::string default_response;
    std::vector<ClientHandler*> clients;
};


#endif //TP_3_SERVER_H
