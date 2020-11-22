//
// Created by andy on 7/11/20.
//

#ifndef TP_3_REQUESTSHANDLER_H
#define TP_3_REQUESTSHANDLER_H

#include <vector>
#include <atomic>
#include <string>
#include "../common_src/Socket.h"
#include "ClientHandler.h"
#include "Thread.h"
#include "../common_src/Printer.h"


class RequestsHandler : public Thread {
public:
    RequestsHandler(const std::string& port,
                    const std::string& default_get_response);
    ~RequestsHandler() override;
    void run() override;
    void stopConnections();
    void cleanConnections();
    void closeAllConnections();

private:
    Socket socket = Socket(true);
    std::atomic<bool> keep_talking;
    std::string port;
    std::vector<ClientHandler*> clients;
    InfoHandler info_handler;
    Printer printer;
};


#endif //TP_3_REQUESTSHANDLER_H
